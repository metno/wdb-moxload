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
#include <mox/ValueParameterHandler.h>
#include <forecast/ForecastCollector.h>
#include <mox/namespace.h>


class ValueParameterTest : public testing::Test
{
public:
	ValueParameterTest(const char * valueParameter = "airPressure") :
		collector(getConverter())
	{
		handler = new mox::ValueParameterHandler(collector, valueParameter, mox::moxNamespace);
		parser = TestingParser(* handler, valueParameter);
	}
	~ValueParameterTest()
	{
		delete handler;
	}

protected:

	const mox::Forecast & standardQuery(const QString & param)
	{
		parser.parse(param);

		const mox::ForecastCollectionPtr f = collector.forecasts();

		if ( f->size() != 1 )
			throw std::runtime_error("Unexpected number of forecasts created");
		return f->front();
	}

	mox::ForecastCollector collector;
	mox::MoxTagHandler * handler;
	TestingParser parser;
};

struct ValueParameterTestAirTemperature : public ValueParameterTest
{
	ValueParameterTestAirTemperature() : ValueParameterTest("airTemperature") {}
};

TEST_F(ValueParameterTestAirTemperature, valueParameterName)
{
	const mox::Forecast & forecast = standardQuery("<wdb:airTemperature uom=\"Cel\">31.0</wdb:airTemperature>");
	ASSERT_EQ("air temperature", forecast.valueParameter());
}

TEST_F(ValueParameterTestAirTemperature, valueParameterToLevelConversion)
{
	const mox::Forecast & forecast = standardQuery("<wdb:airTemperature uom=\"Cel\">31.0</wdb:airTemperature>");
	EXPECT_EQ("height above ground distance", forecast.levelParameter());
	EXPECT_EQ(2, forecast.levelFrom());
	EXPECT_EQ(2, forecast.levelTo());
}


TEST_F(ValueParameterTest, valueParameterName)
{
	const mox::Forecast & forecast = standardQuery("<wdb:airPressure uom=\"hPa\">1017.4</wdb:airPressure>");
	ASSERT_EQ("air pressure", forecast.valueParameter());
}

TEST_F(ValueParameterTest, valueParameterToLevelConversion)
{
	const mox::Forecast & forecast = standardQuery("<wdb:airPressure uom=\"hPa\">1017.4</wdb:airPressure>");
	EXPECT_EQ("height above ground distance", forecast.levelParameter());
	EXPECT_EQ(0, forecast.levelFrom());
	EXPECT_EQ(0, forecast.levelTo());
}

TEST_F(ValueParameterTest, valueAboveZero)
{
	const mox::Forecast & forecast = standardQuery("<wdb:airPressure uom=\"hPa\">1017.4</wdb:airPressure>");
	ASSERT_DOUBLE_EQ(1017.4, forecast.value());
}

TEST_F(ValueParameterTest, valueZero)
{
	const mox::Forecast & forecast = standardQuery("<wdb:airPressure uom=\"hPa\">0</wdb:airPressure>");
	ASSERT_DOUBLE_EQ(0, forecast.value());
}

TEST_F(ValueParameterTest, valueBelowZero)
{
	const mox::Forecast & forecast = standardQuery("<wdb:airPressure uom=\"hPa\">-420.1</wdb:airPressure>");
	ASSERT_DOUBLE_EQ(-420.1, forecast.value());
}
