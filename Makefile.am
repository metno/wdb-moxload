#-----------------------------------------------------------------------------
# Project Makefile for wdb's feltLoad
#
# This file is processed by automake to generate the non-recursive
# project Makefile
#-----------------------------------------------------------------------------


# Scanned by Autoreconf; must be static (no expansion)
ACLOCAL_AMFLAGS = 		-I config

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

include src/moxLoad.mk
include etc/moxLoad.mk
include test/moxLoad.mk


###
# Debian package related stuff
###

PKG_DIR = $(PACKAGE)-$(VERSION)
DEBIAN_DIR = $(PKG_DIR)/debian
DEBIAN_PACKAGE = $(PACKAGE)_$(VERSION)
DEBIAN_VERSION = 1
ARCH = `dpkg-architecture -qDEB_HOST_ARCH_CPU`
DEBIAN_PACKAGE_NAME = $(DEBIAN_PACKAGE)-$(DEBIAN_VERSION)_$(ARCH).deb

debian:	dist clean-debian 
	tar xvzf $(PKG_DIR).tar.gz
	mkdir -p $(DEBIAN_DIR)
	rm -rf $(DEBIAN_DIR)/*
	cp -r $(top_srcdir)/debian_files/* $(DEBIAN_DIR)
	chmod 744 $(DEBIAN_DIR)/rules
	cp $(PKG_DIR).tar.gz $(DEBIAN_PACKAGE).orig.tar.gz
	cd $(PKG_DIR) && dpkg-buildpackage -rfakeroot -us -uc
	lintian $(DEBIAN_PACKAGE_NAME)
#	linda $(DEBIAN_PACKAGE_NAME)

update-debian:
	rm -rf $(DEBIAN_DIR)/*
	cp -r $(top_srcdir)/debian_files/* $(DEBIAN_DIR)
	chmod 744 $(DEBIAN_DIR)/rules
	cd $(PKG_DIR) && dpkg-buildpackage -rfakeroot -us -uc -nc
	lintian $(DEBIAN_PACKAGE_NAME)
#	linda $(DEBIAN_PACKAGE_NAME)


clean-debian:
	debclean
	rm -rf $(PKG_DIR) $(DEBIAN_PACKAGE)*
