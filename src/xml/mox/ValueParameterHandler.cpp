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

#include "ValueParameterHandler.h"
#include <forecast/ForecastCollector.h>
#include <QXmlStreamReader>
#include <stdexcept>
#include <iostream>

namespace mox
{

ValueParameterHandler::ValueParameterHandler(ForecastCollector & processor, const QString & tagName, const QString & tagNamespace) :
	MoxTagHandler(processor, tagName, tagNamespace)
{}

ValueParameterHandler::~ValueParameterHandler()
{}

void ValueParameterHandler::handleStartTag(QXmlStreamReader & reader)
{
	const QString parameterName = reader.name().toString();
	double value;
	QXmlStreamReader::TokenType t = reader.readNext();
	const QString val = reader.text().toString();
	if ( QXmlStreamReader::Characters == t )
	{
		bool ok;
		value = val.toDouble(& ok);
		if ( ! ok )
			throw std::logic_error("Error when converting value content to double: " + val.toStdString());
	}
	else
		throw std::logic_error("Unexpected: " + val.toStdString());

	collector.setValue(parameterName.toStdString(), value);
}

}
