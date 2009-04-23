/*
 moxLoad

 Copyright (C) 2009 met.no

 Contact information:
 Norwegian Meteorological Institute
 Box 43 Blindern
 0313 OSLO
 NORWAY
 E-mail: wdb@met.no

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA  02110-1301, USA
 */

#include <string>
#include <gtest/gtest.h>
#include <QFile>
#include <forecast/Parser.h>

//class ParserTest : public testing::Test
//{};

using boost::posix_time::time_from_string;

class ParserTest : public testing::Test
{
public:
	ParserTest() :
		parser(SRCDIR"/etc/wdbFromMox.conf")
	{}

protected:

	mox::Parser parser;

	const mox::ForecastCollectionPtr parseFile(const char * fileName)
	{
		QFile xmlFile(fileName);
		xmlFile.open(QFile::ReadOnly);
		const mox::ForecastCollectionPtr forecasts = parser.parse(xmlFile);
		return forecasts;
	}

};


TEST_F(ParserTest, readParameterNames)
{
	const mox::ForecastCollectionPtr data = parseFile(SRCDIR"/test/mox/xml/bergen.xml");
	const mox::ForecastCollection & f = * data;

	ASSERT_EQ(11u, f.size());
	try
	{
		EXPECT_EQ("air pressure", f[0].wdbValueParameter());
		EXPECT_EQ("air temperature", f[1].wdbValueParameter());
		EXPECT_EQ("total cloud cover", f[2].wdbValueParameter());
		EXPECT_EQ("low cloud cover", f[3].wdbValueParameter());
		EXPECT_EQ("medium cloud cover", f[4].wdbValueParameter());
		EXPECT_EQ("high cloud cover", f[5].wdbValueParameter());
		EXPECT_EQ("fog cover", f[6].wdbValueParameter());
		EXPECT_EQ("relative humidity", f[7].wdbValueParameter());
		EXPECT_EQ("wind direction", f[8].wdbValueParameter());
		EXPECT_EQ("wind velocity", f[9].wdbValueParameter());
		EXPECT_EQ("accumulated precipitation surface density", f[10].wdbValueParameter());
	}
	catch ( std::exception & e )
	{
		FAIL() << e.what();
	}
}

TEST_F(ParserTest, readAnalysisTime)
{
	const mox::ForecastCollectionPtr data = parseFile(SRCDIR"/test/mox/xml/bergen.xml");
	const mox::ForecastCollection & f = * data;
	ASSERT_EQ(11u, f.size());

	mox::Forecast::Time expectedAnalysisTime = time_from_string("2005-08-11 10:47:00");

	for ( mox::ForecastCollection::const_iterator it = f.begin(); it != f.end(); ++ it )
		ASSERT_EQ(expectedAnalysisTime, it->analysisTime()) << " at parameter " << it->wdbValueParameter();
}

TEST_F(ParserTest, readValidTime)
{
	const mox::ForecastCollectionPtr data = parseFile(SRCDIR"/test/mox/xml/bergen.xml");
	const mox::ForecastCollection & f = * data;
	ASSERT_EQ(11u, f.size());

	mox::Forecast::Time expectedValidTimeFrom = time_from_string("2009-02-10 12:00:00");
	mox::Forecast::Time expectedValidTimeTo   = time_from_string("2009-02-10 12:00:00");

	mox::ForecastCollection::const_iterator almostEnd = f.end();
	-- almostEnd;
	for ( mox::ForecastCollection::const_iterator it = f.begin(); it != almostEnd; ++ it )
	{
		ASSERT_EQ(expectedValidTimeFrom, it->validFrom()) << " at parameter " << it->wdbValueParameter();
		ASSERT_EQ(expectedValidTimeTo, it->validTo()) << " at parameter " << it->wdbValueParameter();
	}
	ASSERT_EQ(time_from_string("2009-02-10 09:00:00"), f.back().validFrom());
	ASSERT_EQ(expectedValidTimeTo, f.back().validTo());
}

TEST_F(ParserTest, readPosition)
{
	const mox::ForecastCollectionPtr data = parseFile(SRCDIR"/test/mox/xml/bergen.xml");
	const mox::ForecastCollection & f = * data;
	ASSERT_EQ(11u, f.size());

	for ( mox::ForecastCollection::const_iterator it = f.begin(); it != f.end(); ++ it )
	{
		ASSERT_DOUBLE_EQ(5.3239, it->location().latitude());
		ASSERT_DOUBLE_EQ(60.3928, it->location().longitude());
	}
}

TEST_F(ParserTest, readPositionName)
{
	const mox::ForecastCollectionPtr data = parseFile(SRCDIR"/test/mox/xml/bergen.xml");
	const mox::ForecastCollection & f = * data;
	ASSERT_EQ(11u, f.size());

	for ( mox::ForecastCollection::const_iterator it = f.begin(); it != f.end(); ++ it )
		ASSERT_EQ("bergen", it->location().locationName());

}
