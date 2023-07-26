# $Id: Makefile.am 339 2020-06-08 16:12:31Z yeti-dn $
if OS_MSWIN
ms_bitfields = -mms-bitfields
EXTRA_DIST = client.c server.c clientserver.h
else
clientserver_programs = client server
client_SOURCES = client.c clientserver.h
server_SOURCES = server.c clientserver.h
endif

noinst_PROGRAMS = \
	$(clientserver_programs) \
	writegwy \
	writegeneric \
	readgeneric \
	readgwy \
	checkgeneric

AM_CFLAGS = $(ms_bitfields) $(WARNING_CFLAGS) -I$(top_srcdir)/lib
AM_LDFLAGS = ../lib/libgwyfile.la -lm -all-static
writegwy_SOURCES = writegwy.c
readgwy_SOURCES = readgwy.c
readgeneric_SOURCES = readgeneric.c
writegeneric_SOURCES = writegeneric.c
checkgeneric_SOURCES = checkgeneric.c

