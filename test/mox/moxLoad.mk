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
	test/mox/ValueParameterTest.cpp

moxLoadTest_CPPFLAGS = \
	-DCONFIG_FILE=\"$(top_srcdir)/etc/wdbFromMox.conf\" \
	$(AM_CPPFLAGS) $(gtest_CFLAGS)

moxLoadTest_LDFLAGS = libmoxBase.a $(AM_LDFLAGS) $(gtest_LIBS) -lgtest_main

endif
