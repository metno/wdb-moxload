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

#include "TimePeriodHandler.h"
#include "namespace.h"
#include <util/timeConversion.h>
#include <QXmlStreamReader>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <stdexcept>

namespace gml
{

TimePeriodHandler::TimePeriodHandler(mox::ForecastCollector & processor) :
	mox::MoxTagHandler(processor, "TimePeriod", gmlNamespace)
{
}

void TimePeriodHandler::handle(QXmlStreamReader & reader)
{
	// BUG: Does not handle generic gml tags

	while (not reader.atEnd())
	{
		//QXmlStreamReader::TokenType token = reader.tokenType();
		QXmlStreamReader::TokenType token = reader.readNext();
		if (QXmlStreamReader::StartElement == token)
		{
			QString tagName = reader.name().toString();
			if ( tagName == "beginPosition" or tagName == "begin" )
			{
				token = reader.readNext();
				if ( QXmlStreamReader::Characters == token )
					from_ = getPtime(reader.text().toString());
				while ( QXmlStreamReader::EndElement != token )
					token = reader.readNext();
			}
			else if ( tagName == "endPosition" or tagName == "end" )
			{
				token = reader.readNext();
				if ( QXmlStreamReader::Characters == token )
					to_ = getPtime(reader.text().toString());
				while ( QXmlStreamReader::EndElement != token )
					token = reader.readNext();
			}
			else
				throw std::logic_error("Unknown tag: " + tagName.toStdString());
		}
		else if ( QXmlStreamReader::EndElement == token )
		{
			return;
		}
	}
}

}
