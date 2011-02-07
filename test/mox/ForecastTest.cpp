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

#include <gtest/gtest.h>
#include "TestingMoxParameterConverter.h"
#include <forecast/Forecast.h>
#include <sstream>


TEST(ForecastTest, generateWciWrite)
{
//	Forecast(double latitude, double longitude, const Time & analysisTime,
//			const Time & validFrom, const Time & validTo,
//			const std::string & valueParameter,
//			double value, boost::shared_ptr<MoxParameterConverter> converter);

	ForecastLocation location("oslo", 10.7464, 59.9111);

	mox::Forecast::Time referenceTime = boost::posix_time::time_from_string("2009-04-21 06:00:00");
	mox::Forecast::Time validFrom = boost::posix_time::time_from_string("2009-04-21 12:00:00");
	mox::Forecast::Time validTo = boost::posix_time::time_from_string("2009-04-21 18:00:00");

	mox::Forecast f(location, referenceTime, validFrom, validTo, "humidity", 93.3, getConverter());

	std::ostringstream expected;
	expected << "SELECT wci.write(93.3::double precision, ";
	//expected << "geomfromtext('POINT(14 15)'), ";
	expected << "'oslo', ";
	expected << "'" << referenceTime << "', ";
	expected << "'" << validFrom << "', ";
	expected << "'" << validTo << "', ";
	expected << "'relative humidity', ";
	expected << "'height above ground', ";
	expected << "2, 2)";

	const std::string expectedResult = expected.str();

	ASSERT_EQ(expectedResult, f.getWciWriteQuery());
}

TEST(ForecastTest, overrideReferenceTime)
{
	ForecastLocation location("oslo", 10.7464, 59.9111);

	mox::Forecast::Time referenceTime = boost::posix_time::time_from_string("2009-04-21 06:00:00");
	mox::Forecast::Time validFrom = boost::posix_time::time_from_string("2009-04-21 12:00:00");
	mox::Forecast::Time validTo = boost::posix_time::time_from_string("2009-04-21 18:00:00");

	mox::Forecast f(location, referenceTime, validFrom, validTo, "humidity", 93.3, getConverter());

	mox::Forecast::Time overrideReferenceTime = boost::posix_time::time_from_string("2009-07-31 06:00:00");

	std::ostringstream expected;
	expected << "SELECT wci.write(93.3::double precision, ";
	//expected << "geomfromtext('POINT(14 15)'), ";
	expected << "'oslo', ";
	expected << "'" << overrideReferenceTime << "', ";
	expected << "'" << validFrom << "', ";
	expected << "'" << validTo << "', ";
	expected << "'relative humidity', ";
	expected << "'height above ground', ";
	expected << "2, 2)";

	const std::string expectedResult = expected.str();

	ASSERT_EQ(expectedResult, f.getWciWriteQuery(overrideReferenceTime));
}

TEST(ForecastTest, generateLoadPlaceDefinition)
{
	ForecastLocation location("oslo", 10.7464, 59.9111);
	mox::Forecast::Time referenceTime = boost::posix_time::time_from_string("2009-04-21 06:00:00");
	mox::Forecast::Time validFrom = boost::posix_time::time_from_string("2009-04-21 12:00:00");
	mox::Forecast::Time validTo = boost::posix_time::time_from_string("2009-04-21 18:00:00");

	mox::Forecast f(location, referenceTime, validFrom, validTo, "humidity", 93.3, getConverter());

	std::string expectedQuery = "SELECT wci.loadPlaceDefinition('point(10.7464 59.9111)', geomfromtext('POINT(10.7464 59.9111)', 4030))";

	ASSERT_EQ(expectedQuery, f.getLoadPlaceDefinitionQuery());
}

TEST(ForecastTest, generateLoadPlaceDefinitionManyDecimalsInLocation)
{
	ForecastLocation location("oslo", 10.746382372312, 59.911114141242);
	mox::Forecast::Time referenceTime = boost::posix_time::time_from_string("2009-04-21 06:00:00");
	mox::Forecast::Time validFrom = boost::posix_time::time_from_string("2009-04-21 12:00:00");
	mox::Forecast::Time validTo = boost::posix_time::time_from_string("2009-04-21 18:00:00");

	mox::Forecast f(location, referenceTime, validFrom, validTo, "humidity", 93.3, getConverter());

	std::string expectedQuery = "SELECT wci.loadPlaceDefinition('point(10.7464 59.9111)', geomfromtext('POINT(10.7464 59.9111)', 4030))";

	ASSERT_EQ(expectedQuery, f.getLoadPlaceDefinitionQuery());
}
