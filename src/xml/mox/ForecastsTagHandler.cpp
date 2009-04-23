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

#include "ForecastsTagHandler.h"
#include <iostream>
#include <QXmlStreamReader>
#include <gml/PointPropertyTypeHandler.h>
#include <gml/TimeInstantPropertyTypeHandler.h>
#include "AnalysisTimeHandler.h"
#include <gml/TimePrimitivePropertyTypeHandler.h>
#include "ForecastMemberTypeHandler.h"
#include "namespace.h"
#include <gml/namespace.h>

namespace mox
{

typedef mox::MoxTagHandler Handler;
typedef Handler DescriptionHandler;
typedef Handler ObservedPropertyHandler;
typedef gml::PointPropertyTypeHandler ForecastPointHandler;
typedef gml::TimeInstantPropertyTypeHandler IssueTimeHandler;
typedef gml::TimeInstantPropertyTypeHandler NextIssueTimeHandler;
typedef gml::TimePrimitivePropertyTypeHandler ValidTimeHandler;
typedef ForecastMemberTypeHandler ForecastHandler;



ForecastsTagHandler::ForecastsTagHandler(mox::ForecastCollector & processor) :
	MoxTagHandler(processor, "Forecasts", moxNamespace)
{
	subHandlers.push_back(new DescriptionHandler(processor, "description", gml::gmlNamespace));
	subHandlers.push_back(new ObservedPropertyHandler(processor, "procedure", moxNamespace));
	subHandlers.push_back(new ObservedPropertyHandler(processor, "observedProperty", moxNamespace));
	subHandlers.push_back(new ForecastPointHandler(processor, "forecastPoint", moxNamespace));
	subHandlers.push_back(new AnalysisTimeHandler(processor));
	subHandlers.push_back(new IssueTimeHandler(processor, "issueTime", moxNamespace));;
	subHandlers.push_back(new NextIssueTimeHandler(processor, "nextIssueTime", moxNamespace));
	subHandlers.push_back(new ValidTimeHandler(processor, "validTime", moxNamespace));
	subHandlers.push_back(new ForecastHandler(processor, "forecast", moxNamespace));
}

}
