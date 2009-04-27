if HAVE_GTEST

TESTS = moxLoadTest

check_PROGRAMS = moxLoadTest

moxLoadTest_SOURCES = \
	test/mox/ForecastPointTest.cpp \
	test/mox/ForecastTest.cpp \
	test/mox/MoxParameterConversionTest.cpp \
	test/mox/ParserTest.cpp \
	test/mox/TestingMoxParameterConverter.h \
	test/mox/TestingMoxParameterConverter.cpp \
	test/mox/TestingParser.cpp \
	test/mox/TestingParser.h \
	test/mox/ValidTimeTest.cpp \
	test/mox/ValueParameterTest.cpp \
	src/configuration/testConfigFileLookup.cpp \
	src/configuration/configFileLookup.h	
	

moxLoadTest_CPPFLAGS = \
	-DSRCDIR=\"$(top_srcdir)\" \
	$(AM_CPPFLAGS) $(gtest_CFLAGS)

moxLoadTest_LDFLAGS = libmoxBase.a $(AM_LDFLAGS) $(gtest_LIBS) -lgtest_main

include test/mox/xml/moxLoad.mk

endif
