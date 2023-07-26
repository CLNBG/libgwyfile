# $Id: Makefile.am 394 2022-02-11 15:40:12Z yeti-dn $
if OS_MSWIN
no_undefined = -no-undefined
export_symbols = -export-symbols gwyfile.def
ms_bitfields = -mms-bitfields
endif

gwyfileincludedir = $(includedir)/gwyfile
pkgconfigdatadir = $(libdir)/pkgconfig

# In following order do:
# Any code change     C:   R++: A
# Any iface change    C++: 0:   A
# Adding ifaces       C:   R:   A++
# Changing ifaces     C:   R:   0
libversion = -version-info 4:0:4

lib_LTLIBRARIES = libgwyfile.la
gwyfileinclude_HEADERS = gwyfile.h
pkgconfigdata_DATA = gwyfile.pc
libgwyfile_la_SOURCES = gwyfile.c gwyfile.h
libgwyfile_la_LDFLAGS = $(no_undefined) $(export_symbols) $(libversion)
AM_CFLAGS = $(ms_bitfields) $(WARNING_CFLAGS)
EXTRA_DIST = \
	Doxyfile \
	filter-out-attrs.sed \
	filter-out-attrs.sh \
	gwyfile.def \
	gwyfile.pc.in \
	gwyfile.vim

clean-local:
	rm -rf doc

update-def:
	echo EXPORTS >gwyfile.def
	sed 's/^[A-Za-z0-9_* ]* \(gwyfile_[a-z0-9_]\+\) *(.*$$/    \1/;t;d' gwyfile.h | sort >>gwyfile.def

if HAVE_DOXYGEN
doc: $(libgwyfile_la_SOURCES) Doxyfile
	$(AM_V_GEN)$(DOXYGEN) Doxyfile
else
doc:
	@echo "Doxygen is required to build documentation."
	@false
endif
