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
#include "TestingParser.h"
#include "TestingMoxParameterConverter.h"
#include <mox/ForecastTypeHandler.h>
#include <forecast/ForecastCollector.h>
#include <forecast/Parser.h>
#include <configuration/configFileLookup.h>
#include <metno/namespace.h>
#include <QFile>
#include <functional>
#include <algorithm>

class SeaMovementTest : public testing::Test
{
public:
	SeaMovementTest() :
		collector(getConverter())
	{
		handler = new mox::ForecastTypeHandler(collector, "OceanForecast", metno::metnoNamespace, getConfigFile("OceanForecast.conf").file_string());
		parser = TestingParser(* handler, "OceanForecast");
	}
	~SeaMovementTest()
	{
		delete handler;
	}

protected:
	mox::ForecastCollector collector;
	mox::MoxTagHandler * handler;
	TestingParser parser;
};

struct has_parameter_name : public std::unary_function<mox::Forecast, bool>
{
	std::string wantedMoxParameter_;
	has_parameter_name(const std::string & wantedMoxParameter) : wantedMoxParameter_(wantedMoxParameter) {}

	bool operator () (const mox::Forecast & forecast) const
	{
		return forecast.moxValueParameter() == wantedMoxParameter_;
	}
};

TEST_F(SeaMovementTest, convertParameterNorthEast)
{
	parser.parse(
			"<metno:OceanForecast gml:id=\"f-1\">\n"
			"   <wdb:seaCurrentDirection uom=\"deg\">45</wdb:seaCurrentDirection>\n"
			"   <wdb:seaCurrentSpeed uom=\"m/s\">10</wdb:seaCurrentSpeed>\n"
			"</metno:OceanForecast>");

	const mox::ForecastCollection & forecasts = * collector.forecasts();

	ASSERT_EQ(2u, forecasts.size());

	mox::ForecastCollection::const_iterator uVector = std::find_if(forecasts.begin(), forecasts.end(), has_parameter_name("seaCurrentVelocityU"));
	mox::ForecastCollection::const_iterator vVector = std::find_if(forecasts.begin(), forecasts.end(), has_parameter_name("seaCurrentVelocityV"));

	ASSERT_TRUE(uVector != forecasts.end());
	ASSERT_TRUE(vVector != forecasts.end());

	EXPECT_NEAR(7.0710678118654755, uVector->value(), 0.000000000000001);
	EXPECT_NEAR(7.0710678118654755, vVector->value(), 0.000000000000001);
}

TEST_F(SeaMovementTest, convertParameterWest)
{
	parser.parse(
			"<metno:OceanForecast gml:id=\"f-1\">\n"
			"   <wdb:seaCurrentDirection uom=\"deg\">-90</wdb:seaCurrentDirection>\n"
			"   <wdb:seaCurrentSpeed uom=\"m/s\">15</wdb:seaCurrentSpeed>\n"
			"</metno:OceanForecast>");

	const mox::ForecastCollection & forecasts = * collector.forecasts();

	ASSERT_EQ(2u, forecasts.size());

	mox::ForecastCollection::const_iterator uVector = std::find_if(forecasts.begin(), forecasts.end(), has_parameter_name("seaCurrentVelocityU"));
	mox::ForecastCollection::const_iterator vVector = std::find_if(forecasts.begin(), forecasts.end(), has_parameter_name("seaCurrentVelocityV"));

	ASSERT_TRUE(uVector != forecasts.end());
	ASSERT_TRUE(vVector != forecasts.end());

	EXPECT_NEAR(-15, uVector->value(), 0.000000000000001);
	EXPECT_NEAR(0, vVector->value(), 0.000000000000001);
}

TEST_F(SeaMovementTest, missingSeaCurrentDirection)
{
	parser.parse(
			"<metno:OceanForecast gml:id=\"f-1\">\n"
			"   <wdb:seaCurrentSpeed uom=\"m/s\">15</wdb:seaCurrentSpeed>\n"
			"</metno:OceanForecast>\n");

	const mox::ForecastCollection & forecasts = * collector.forecasts();

	ASSERT_TRUE(forecasts.empty());
}

TEST_F(SeaMovementTest, missingSeaCurrentSpeed)
{
	parser.parse(
			"<metno:OceanForecast gml:id=\"f-1\">\n"
			"   <wdb:seaCurrentDirection uom=\"deg\">-90</wdb:seaCurrentDirection>\n"
			"</metno:OceanForecast>\n");

	const mox::ForecastCollection & forecasts = * collector.forecasts();

	ASSERT_TRUE(forecasts.empty());
}

/// What if speed and direction does not belong to each other?
TEST_F(SeaMovementTest, speedDirectionMismatch)
{
	QFile xmlFile(SRCDIR"/test/mox/xml/oceanforecast_speedDirectionMismatch.xml");
	xmlFile.open(QFile::ReadOnly);
	mox::Parser parser(SRCDIR"/etc/wdbFromMox.conf");

	const mox::ForecastCollectionPtr forecasts = parser.parse(xmlFile);

	ASSERT_TRUE(forecasts->empty());
}


/*
"<metno:OceanForecast gml:id=\"f-1\">\n"
"   <wdb:seaIcePresence>0</wdb:seaIcePresence>\n"
"   <wdb:meanTotalWaveDirection uom=\"deg\">161.7</wdb:meanTotalWaveDirection>\n"
"   <wdb:significantTotalWaveHeight uom=\"m\">1.4</wdb:significantTotalWaveHeight>\n"
"   <wdb:seaCurrentDirection uom=\"deg\">271.0</wdb:seaCurrentDirection>\n"
"   <wdb:seaCurrentSpeed uom=\"m/s\">0.08</wdb:seaCurrentSpeed>\n"
"   <wdb:seaSurfaceHeight uom=\"m\">-0.1</wdb:seaSurfaceHeight>\n"
"   <wdb:seaTemperature uom=\"Cel\">7.5</wdb:seaTemperature>\n"
"</metno:OceanForecast>"
*/
