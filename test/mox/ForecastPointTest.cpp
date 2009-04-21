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
#include <gml/PointPropertyTypeHandler.h>
#include <forecast/ForecastCollector.h>
#include <QString>
#include <QXmlStreamReader>
#include <stdexcept>

class ForecastPointTest : public testing::Test
{
protected:
	mox::ForecastCollector collector;

	void parse(const QString & xml)
	{
		static const QString head = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
			"<wdb:Forecasts gml:id=\"fc20090130\" xmlns=\"http://api.met.no\"\n"
			"xmlns:metno=\"http://api.met.no\"\n"
			"xmlns:wdb=\"http://wdb.met.no/wdbxml\"\n"
			"xmlns:gml=\"http://www.opengis.net/gml/3.2\"\n"
			"xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n"
			"xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\n"
			"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
			"xsi:schemaLocation=\"http://api.met.no file:///home/vegardb/workspace/mox/schemas/metno.xsd\">\n";
		static const QString tail = "\n</wdb:Forecasts>\n";

		QXmlStreamReader reader(head + xml + tail);
		gml::PointPropertyTypeHandler h(collector, "forecastPoint", "http://wdb.met.no/wdbxml");

		reader.readNext();
		while ( reader.tokenType() != QXmlStreamReader::StartElement or reader.name() != "forecastPoint" )
			reader.readNext();
		h.handle(reader);
	}
public:
	ForecastPointTest() :
		collector(getConverter())
	{}
};


TEST_F(ForecastPointTest, test)
{
	parse("<wdb:forecastPoint>\n"
		" <gml:Point gml:id=\"oslo\" srsName=\"EPSG:4326\">\n"
		"  <gml:pos>38.99 -77.99</gml:pos>\n"
		" </gml:Point>\n"
		"</wdb:forecastPoint>");

	const ForecastLocation & loc = collector.location();

	EXPECT_DOUBLE_EQ(38.99, loc.latitude());
	EXPECT_DOUBLE_EQ(-77.99, loc.longitude());
	EXPECT_EQ("oslo", loc.locationName());
}

TEST_F(ForecastPointTest, test2)
{
	parse("<wdb:forecastPoint>\n"
		" <gml:Point gml:id=\"sortland\" srsName=\"EPSG:4326\">\n"
		"  <gml:pos>15.4161 68.6931</gml:pos>\n"
		" </gml:Point>\n"
		"</wdb:forecastPoint>");

	const ForecastLocation & loc = collector.location();

	EXPECT_DOUBLE_EQ(15.4161, loc.latitude());
	EXPECT_DOUBLE_EQ(68.6931, loc.longitude());
	EXPECT_EQ("sortland", loc.locationName());
}

TEST_F(ForecastPointTest, invalidContent)
{
	ASSERT_THROW(
		parse("<wdb:forecastPoint>\n"
			" <gml:Point gml:id=\"sortland\" srsName=\"EPSG:4326\">\n"
			"  <gml:pos>foo</gml:pos>\n"
			" </gml:Point>\n"
			"</wdb:forecastPoint>"),
		std::logic_error);
}
