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

#include "ForecastTypeHandler.h"
#include "namespace.h"
#include <gml/PointPropertyTypeHandler.h>
#include <gml/TimeInstantPropertyTypeHandler.h>
#include "AnalysisTimeHandler.h"
#include "ValidTimeHandler.h"
#include <gml/TimePrimitivePropertyTypeHandler.h>
#include <boost/assign.hpp>


namespace mox
{
typedef MoxTagHandler Handler;
typedef Handler ObservedPropertyHandler;
typedef gml::PointPropertyTypeHandler ForecastPointHandler;
typedef gml::TimeInstantPropertyTypeHandler IssueTimeHandler;
typedef gml::TimeInstantPropertyTypeHandler NextIssueTimeHandler;

ForecastTypeHandler::ForecastTypeHandler(ForecastCollector & processor, const QString & tagName, const QString & tagNamespace) :
	MoxTagHandler(processor, tagName, tagNamespace)
{
	using namespace boost::assign;

	HandlerList acceptedElements;
	acceptedElements +=
		new ObservedPropertyHandler(processor, "procedure", moxNamespace),
		new ObservedPropertyHandler(processor, "observedProperty", moxNamespace),
		new ForecastPointHandler(processor, "forecastPoint", moxNamespace),
		new AnalysisTimeHandler(processor),
		new IssueTimeHandler(processor, "issueTime", moxNamespace),
		new NextIssueTimeHandler(processor, "nextIssueTime", moxNamespace),
		new ValidTimeHandler(processor);

	// Elements will be inserted before any elements from subclasses
	subHandlers.insert(subHandlers.begin(), acceptedElements.begin(), acceptedElements.end());
}

}
