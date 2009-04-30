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

#include "TestingParser.h"
#include <QXmlStreamReader>
#include <stdexcept>
#include <iostream>

TestingParser::TestingParser() :
	handler(0)
{
}

TestingParser::TestingParser(mox::MoxTagHandler & handler, QString tagName) :
	handler(& handler), tagName(tagName)
{
}

TestingParser::~TestingParser()
{
}

void TestingParser::parse(const QString & xml)
{
	static const QString head = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
		"<wdb:Forecasts gml:id=\"fc20090130\" xmlns=\"http://api.met.no\"\n"
		"xmlns:metno=\"http://api.met.no\"\n"
		"xmlns:wdb=\"http://wdb.met.no/wdbxml\"\n"
		"xmlns:gml=\"http://www.opengis.net/gml/3.2\"\n"
		"xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n"
		"xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\n"
		"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
		"xsi:schemaLocation=\"http://api.met.no file:///home/vegardb/workspace/mox/schemas/metno.xsd\">\n";
	static const QString tail = "\n</wdb:Forecasts>\n";

	QString xmlDocument = head + xml + tail;

	QXmlStreamReader reader(xmlDocument);

	reader.readNext();
	while ( 1 )
	{
		while ( reader.tokenType() != QXmlStreamReader::StartElement )
		{
			reader.readNext();
			if ( reader.atEnd() )
				throw std::logic_error("At end of xml");
		}
		if ( reader.name() == tagName )
			break;
		reader.readNext();
	}
	handler->handle(reader);
}
