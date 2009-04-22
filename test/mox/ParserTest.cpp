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

const mox::ForecastCollectionPtr parseFile(const char * fileName)
{
	QFile xmlFile(fileName);
	xmlFile.open(QFile::ReadOnly);
	const mox::ForecastCollectionPtr forecasts = mox::parse(xmlFile);
	return forecasts;
}

TEST(ParserTest, DISABLED_readParameterNames)
{
	const mox::ForecastCollectionPtr data = parseFile("../test/mox/xml/bergen.xml");
	const mox::ForecastCollection & f = * data;

	ASSERT_EQ(11u, f.size());
	try
	{
		EXPECT_EQ("air pressure", f[0].valueParameter());
		EXPECT_EQ("air temperature", f[1].valueParameter());
		EXPECT_EQ("total cloud cover", f[2].valueParameter());
		EXPECT_EQ("low cloud cover", f[3].valueParameter());
		EXPECT_EQ("medium cloud cover", f[4].valueParameter());
		EXPECT_EQ("high cloud cover", f[5].valueParameter());
		EXPECT_EQ("fog cover", f[6].valueParameter());
		EXPECT_EQ("relative humidity", f[7].valueParameter());
		EXPECT_EQ("wind direction", f[8].valueParameter());
		EXPECT_EQ("wind velocity", f[9].valueParameter());
		EXPECT_EQ("accumulated precipitation surface density", f[10].valueParameter());
	}
	catch ( std::exception & e )
	{
		FAIL() << e.what();
	}
}

TEST(ParserTest, DISABLED_readAnalysisTime)
{
	const mox::ForecastCollectionPtr data = parseFile("../test/mox/xml/bergen.xml");
	const mox::ForecastCollection & f = * data;
	ASSERT_EQ(11u, f.size());

	mox::Forecast::Time expectedAnalysisTime = time_from_string("2005-08-11 10:43:00");

	for ( mox::ForecastCollection::const_iterator it = f.begin(); it != f.end(); ++ it )
		ASSERT_EQ(expectedAnalysisTime, it->analysisTime()) << " at parameter " << it->valueParameter();
}

TEST(ParserTest, DISABLED_readValidTime)
{
	const mox::ForecastCollectionPtr data = parseFile("../test/mox/xml/bergen.xml");
	const mox::ForecastCollection & f = * data;
	ASSERT_EQ(11u, f.size());

	mox::Forecast::Time expectedValidTimeFrom = time_from_string("2009-02-10 12:00:00");
	mox::Forecast::Time expectedValidTimeTo   = time_from_string("2009-02-10 12:00:00");

	mox::ForecastCollection::const_iterator almostEnd = f.end();
	-- almostEnd;
	for ( mox::ForecastCollection::const_iterator it = f.begin(); it != almostEnd; ++ it )
	{
		ASSERT_EQ(expectedValidTimeFrom, it->validFrom()) << " at parameter " << it->valueParameter();
		ASSERT_EQ(expectedValidTimeTo, it->validTo()) << " at parameter " << it->valueParameter();
	}
	ASSERT_EQ(time_from_string("2009-02-10 09:00:00"), f.back().validFrom());
	ASSERT_EQ(expectedValidTimeTo, f.back().validTo());
}

TEST(ParserTest, DISABLED_readPosition)
{
	const mox::ForecastCollectionPtr data = parseFile("../test/mox/xml/bergen.xml");
	const mox::ForecastCollection & f = * data;
	ASSERT_EQ(11u, f.size());

	for ( mox::ForecastCollection::const_iterator it = f.begin(); it != f.end(); ++ it )
	{
		ASSERT_DOUBLE_EQ(5.3239, it->location().latitude());
		ASSERT_DOUBLE_EQ(60.3928, it->location().longitude());
	}
}

TEST(ParserTest, DISABLED_readPositionName)
{
	const mox::ForecastCollectionPtr data = parseFile("../test/mox/xml/bergen.xml");
	const mox::ForecastCollection & f = * data;
	ASSERT_EQ(11u, f.size());

	for ( mox::ForecastCollection::const_iterator it = f.begin(); it != f.end(); ++ it )
		ASSERT_EQ("bergen", it->location().locationName());

}
