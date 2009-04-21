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

#include "PointTypeHandler.h"
#include "namespace.h"
#include <forecast/ForecastCollector.h>
#include <QXmlStreamReader>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <functional>

namespace gml
{

PointTypeHandler::PointTypeHandler(mox::ForecastCollector & processor) :
	mox::MoxTagHandler(processor, "Point", gmlNamespace)
{
	//subHandlers.push_back(new mox::MoxTagHandler(processor, "pos", gmlNamespace));
}

class is_tag : public std::unary_function<QXmlStreamAttribute, bool>
{
	QString namespaceUri_;
	QString name_;

public:
	is_tag(const QString & namespaceUri, const QString & name) :
		namespaceUri_(namespaceUri), name_(name)
	{}

	bool operator () (const QXmlStreamAttribute & attribute) const
	{
		return attribute.namespaceUri().toString() == namespaceUri_ and attribute.name().toString() == name_;
	}
};

void PointTypeHandler::handle(QXmlStreamReader & reader)
{
	const QXmlStreamAttributes & attr = reader.attributes();

	QXmlStreamAttributes::const_iterator find = std::find_if(attr.begin(), attr.end(), is_tag(gmlNamespace,  "id"));
	if ( find != attr.end() )
	{
		std::string locationName = find->value().toString().toStdString();
		ForecastLocation loc(locationName);
		collector.location() = loc;
	}

	while (not reader.atEnd())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (QXmlStreamReader::StartElement == token)
		{
			QString tagName = reader.name().toString();
			if ( tagName == "pos" )
			{
				token = reader.readNext();
				if ( QXmlStreamReader::Characters == token )
					parsePos(reader.text().toString());
				while ( QXmlStreamReader::EndElement != token )
					token = reader.readNext();
			}
			else
				throw std::logic_error("Unknown tag: " + tagName.toStdString() + " (expected Point)");
		}
		else if ( QXmlStreamReader::EndElement == token )
			return;
	}
}


void PointTypeHandler::parsePos(const QString & data)
{
	std::istringstream s(data.toStdString());

	double lat;
	double lon;
	s >> lat;
	s >> lon;

	if ( ! s )
		throw std::logic_error("Ivalid data in pos tag: " + data.toStdString());

	collector.location().latitude(lat);
	collector.location().longitude(lon);
}

}
