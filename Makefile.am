#-----------------------------------------------------------------------------
# Project Makefile for wdb's feltLoad
#
# This file is processed by automake to generate the non-recursive
# project Makefile
#-----------------------------------------------------------------------------


# Scanned by Autoreconf; must be static (no expansion)
ACLOCAL_AMFLAGS = 		-I m4

# Share directory organization
wdblibdir = 	$(libdir)/wdb
pkgsysconfdir = @sysconfdir@/moxLoad


AM_CPPFLAGS = \
	-DSYSCONFDIR=\"$(pkgsysconfdir)\" \
	-I$(top_srcdir)/src/ -I$(top_srcdir)/src/xml \
	$(wdb_CFLAGS) \
	$(QtXml_CFLAGS) $(QtCore_CFLAGS)


AM_LDFLAGS = $(wdb_LIBS) $(QtXml_LIBS) $(QtCore_LIBS)

# Setting Targets

noinst_LIBRARIES = libmoxBase.a
libmoxBase_a_SOURCES =

wdblib_PROGRAMS = moxLoad
moxLoad_CPPFLAGS = $(AM_CPPFLAGS) $(libpqxx_CFLAGS)
moxLoad_LDFLAGS = $(AM_LDFLAGS) $(libpqxx_LIBS)
moxLoad_LDADD = libmoxBase.a
moxLoad_SOURCES =

install-data-hook:	install-user
	
install-user:
	$(WDB_ADMINISTRATION) createuser moxload write



EXTRA_DIST =
CLEANFILES =

include src/moxLoad.mk
include etc/moxLoad.mk
include test/moxLoad.mk
include doc/moxLoad.mk

include mk/debian.mk

debian: common-debian