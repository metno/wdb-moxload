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

#include "AnalysisTimeHandler.h"
#include <forecast/ForecastCollector.h>
#include "namespace.h"
#include <QXmlStreamReader>

namespace mox
{

AnalysisTimeHandler::AnalysisTimeHandler(mox::ForecastCollector & processor)	:
	gml::TimeInstantPropertyTypeHandler(processor, "analysisTime", moxNamespace)
{
}

AnalysisTimeHandler::~AnalysisTimeHandler()
{
}

void AnalysisTimeHandler::handleStartTag(QXmlStreamReader & reader)
{
	Forecast::Time t = boost::posix_time::time_from_string("2005-Aug-11 10:43:00");
	collector.setAnalysisTime(t);
}

}
