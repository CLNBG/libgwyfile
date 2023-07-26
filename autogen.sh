#!/bin/sh
test -d m4 || mkdir m4

##### Generate SOURCES and valgrind test rules for tests
valgrind_template='@NAME@-valgrind.sh: @NAME@$(EXEEXT)
	$(AM_V_at)echo $(LIBTOOL) --mode=execute $(VALGRIND) --quiet --leak-check=full --error-exitcode=1 @NAME@ >@NAME@-valgrind.sh
	$(AM_V_at)chmod 755 @NAME@-valgrind.sh
'

checkprograms=$(sed -ne 's/^check_PROGRAMS *= *\\//;t n;d;:n N;s/ *\\$//;t n;s/[\n\t ]\+/ /g;s/^ *//;s/ *$//;p' test/Makefile.am)

echo "$checkprograms" | sed 's/\(\w\+\)\s*/\1_SOURCES = \1.c common.h\n/g;/^$/d' >checkprograms1.tmp
sed '/@@@ SOURCES BEGIN @@@/,/@@@ SOURCES END @@@/!b;/^#/!d' test/Makefile.am \
    | sed '/@@@ SOURCES BEGIN @@@/r checkprograms1.tmp' >checkprograms2.tmp

rm -f checkprograms3.tmp
vlist=
for x in $checkprograms; do
    echo "$valgrind_template" | sed "s/@NAME@/$x/g" >>checkprograms3.tmp
    vlist="$vlist $x-valgrind.sh"
done

sed '/@@@ VALGRIND BEGIN @@@/,/@@@ VALGRIND END @@@/!b;/^#/!d' checkprograms2.tmp \
    | sed '/@@@ VALGRIND BEGIN @@@/r checkprograms3.tmp' >checkprograms4.tmp

sed "s/^valgrind_tests =.*/valgrind_tests =$vlist/" checkprograms4.tmp >test/Makefile.am
rm -f checkprograms[1234].tmp
#####

libtoolize --copy --install --force
aclocal -I m4
autoheader --force
automake --add-missing --copy --force-missing
autoconf --force
./configure "$@"
