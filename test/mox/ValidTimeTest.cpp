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
#include <mox/ValidTimeHandler.h>
#include <forecast/ForecastCollector.h>

using boost::posix_time::time_from_string;

class ValidTimeTest : public testing::Test
{
public:
	ValidTimeTest() :
		collector(getConverter())
	{
		handler = new mox::ValidTimeHandler(collector);
		parser = TestingParser(* handler, "validTime");
	}
	~ValidTimeTest()
	{
		delete handler;
	}

protected:
	mox::ForecastCollector collector;
	mox::MoxTagHandler * handler;
	TestingParser parser;
};

TEST_F(ValidTimeTest, TimePeriodEqualFromAndTo)
{
	parser.parse("<wdb:validTime>\n"
			" <gml:TimePeriod gml:id=\"t1\">\n"
			"  <gml:beginPosition>2009-02-10T12:00:00Z</gml:beginPosition>\n"
			"  <gml:endPosition>2009-02-10T12:00:00Z</gml:endPosition>\n"
			" </gml:TimePeriod>\n"
			"</wdb:validTime>");

	ASSERT_EQ(time_from_string("2009-02-10 12:00:00"), collector.validTo());
	ASSERT_EQ(time_from_string("2009-02-10 12:00:00"), collector.validTo());
}

TEST_F(ValidTimeTest, TimePeriodDifferentFromAndTo)
{
	parser.parse("<wdb:validTime>\n"
			" <gml:TimePeriod gml:id=\"t1\">\n"
			"  <gml:beginPosition>2009-02-10T12:00:00Z</gml:beginPosition>\n"
			"  <gml:endPosition>2009-02-10T18:00:00Z</gml:endPosition>\n"
			" </gml:TimePeriod>\n"
			"</wdb:validTime>");

	ASSERT_EQ(time_from_string("2009-02-10 12:00:00"), collector.validFrom());
	ASSERT_EQ(time_from_string("2009-02-10 18:00:00"), collector.validTo());
}

TEST_F(ValidTimeTest, TimeInstant)
{
	parser.parse("<wdb:validTime>\n"
			" <gml:TimeInstant>\n"
			"  <gml:timePosition>2009-02-11T12:00:00Z</gml:timePosition>\n"
			" </gml:TimeInstant>\n"
			"</wdb:validTime>");

	ASSERT_EQ(time_from_string("2009-02-11 12:00:00"), collector.validFrom());
	ASSERT_EQ(collector.validFrom(), collector.validTo());

}

TEST_F(ValidTimeTest, noContent)
{
	parser.parse("<wdb:validTime>\n</wdb:validTime>");
	ASSERT_TRUE(collector.validFrom().is_not_a_date_time());
	ASSERT_TRUE(collector.validTo().is_not_a_date_time());
}

TEST_F(ValidTimeTest, noContentInTimeInstant)
{
	parser.parse("<wdb:validTime>\n"
			" <gml:TimeInstant>\n"
			" </gml:TimeInstant>\n"
			"</wdb:validTime>");

	ASSERT_TRUE(collector.validFrom().is_not_a_date_time());
	ASSERT_TRUE(collector.validTo().is_not_a_date_time());
}

TEST_F(ValidTimeTest, noContentInTimePeriod)
{
	parser.parse("<wdb:validTime>\n"
			" <gml:TimePeriod gml:id=\"t1\">\n"
			" </gml:TimePeriod>\n"
			"</wdb:validTime>");

	ASSERT_TRUE(collector.validFrom().is_not_a_date_time());
	ASSERT_TRUE(collector.validTo().is_not_a_date_time());
}
