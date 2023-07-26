# $Id: configure.ac 403 2023-04-24 09:22:41Z yeti-dn $
AC_INIT([libgwyfile], [1.6], [yeti@gwyddion.net])
AC_PREREQ(2.60)
AC_CONFIG_SRCDIR([lib/gwyfile.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_FILES([Makefile lib/Makefile examples/Makefile test/Makefile
                 lib/gwyfile.pc])
AC_CONFIG_HEADERS([config.h])
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([1.11 foreign dist-xz no-dist-gzip])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_PROG_CC
AC_USE_SYSTEM_EXTENSIONS
AC_C_BIGENDIAN
AC_HEADER_ASSERT
AC_CHECK_HEADERS([unistd.h])
LT_INIT([win32-dll,dlopen])
AC_PROG_INSTALL
AC_CHECK_PROGS([DOXYGEN],[doxygen],[:])
AM_CONDITIONAL([HAVE_DOXYGEN],[test "$DOXYGEN" != ":"])
AC_ARG_WITH([valgrind],[Run tests also under valgrind],
            [enable_valgrind=$withval],[enable_valgrind=yes])
if test x$enable_valgrind != xno; then
  AC_CHECK_PROGS([VALGRIND],[valgrind],[:])
else
  VALGRIND=:
fi
AM_CONDITIONAL([HAVE_VALGRIND],[test "$VALGRIND" != ":"])
AC_MSG_CHECKING([for native Microsoft Windows])
case "$host_os" in
  mingw*) os_mswin=yes;;
  *) os_mswin=no;;
esac
AC_MSG_RESULT([$os_mswin])
AM_CONDITIONAL([OS_MSWIN],[test "$os_mswin" = "yes"])
if test "$GCC" = yes; then
  WARNING_CFLAGS="-Wall -W"
fi
AC_SUBST([WARNING_CFLAGS])
AC_OUTPUT
# vim: set ts=2 sw=2 et :
