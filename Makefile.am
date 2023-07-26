# $Id: Makefile.am 252 2016-01-07 23:04:25Z yeti-dn $
SUBDIRS = lib examples test
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = autogen.sh msvc2015

doc:
	(cd lib && $(MAKE) $(AM_MAKEFLAGS) doc)

.PHONY: doc
