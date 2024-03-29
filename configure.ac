#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Pre-Conf
#-----------------------------------------------------------------------------

AC_PREREQ(2.59)
AC_INIT(moxLoad, 0.9.5, [wdb@met.no])
# Config
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])

AC_PROG_LIBTOOL

#-----------------------------------------------------------------------------
# Programs
#-----------------------------------------------------------------------------

AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LN_S
WDB_DOCBOOK_CHECK

#-----------------------------------------------------------------------------
# Checks
#-----------------------------------------------------------------------------

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h stdlib.h sys/time.h unistd.h wordexp.h ctype.h])
AC_CHECK_HEADERS([string vector iterator iosfwd iostream sstream fstream])
AC_CHECK_HEADERS([cmath algorithm memory new stdexcept cstdlib exception])

# string exception sstream 

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MEMCMP

# Check for libraries.
AC_CXX_REQUIRE_STL
VL_LIB_READLINE

#-----------------------------------------------------------------------------
# Module Checks
#-----------------------------------------------------------------------------

# wdb
WDB_LOADERBASE_CHECK
WDB_CHECK

# log4cpp
WDB_LOG4CPP_CHECK(0.3.5rc3)

# Qt
QT_XML_CHECK
QT_CORE_CHECK


# BOOST
WDB_BOOST_CHECK(1.33.1)

# libpqxx
WDB_PQXX_CHECK(2.6.8)


# googletest
GTEST_CHECK

#-----------------------------------------------------------------------------
# documentation
#-----------------------------------------------------------------------------

WDB_DOCBOOK_CHECK

#-----------------------------------------------------------------------------
# Automake
#-----------------------------------------------------------------------------

AM_INIT_AUTOMAKE(-Wall -Werror subdir-objects)
AM_PROG_CC_C_O



#-----------------------------------------------------------------------------
# Configure and Exit
#-----------------------------------------------------------------------------

# Configuration Files
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
