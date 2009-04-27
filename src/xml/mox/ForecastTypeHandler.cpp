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
#include "ValueParameterHandler.h"
#include "AnalysisTimeHandler.h"
#include "ValidTimeHandler.h"
#include <gml/TimePrimitivePropertyTypeHandler.h>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
//#include <fstream>
#include <stdexcept>

using namespace std;
namespace fs = boost::filesystem;

namespace mox
{
typedef MoxTagHandler Handler;
typedef Handler ObservedPropertyHandler;
typedef gml::PointPropertyTypeHandler ForecastPointHandler;
typedef gml::TimeInstantPropertyTypeHandler IssueTimeHandler;
typedef gml::TimeInstantPropertyTypeHandler NextIssueTimeHandler;

ForecastTypeHandler::ForecastTypeHandler(ForecastCollector & processor, const QString & tagName, const QString & tagNamespace, const fs::path & parameterListFile) :
	MoxTagHandler(processor, tagName, tagNamespace)
{
	subHandlers.push_back(new ObservedPropertyHandler(processor, "procedure", moxNamespace));
	subHandlers.push_back(new ObservedPropertyHandler(processor, "observedProperty", moxNamespace));
	subHandlers.push_back(new ForecastPointHandler(processor, "forecastPoint", moxNamespace));
	subHandlers.push_back(new AnalysisTimeHandler(processor));
	subHandlers.push_back(new IssueTimeHandler(processor, "issueTime", moxNamespace));
	subHandlers.push_back(new NextIssueTimeHandler(processor, "nextIssueTime", moxNamespace));
	subHandlers.push_back(new ValidTimeHandler(processor));

	fs::ifstream conf(parameterListFile);
	if ( ! conf )
		throw runtime_error("Unable to open configuration file: " + parameterListFile.file_string());

	string moxParameterName;
	while ( conf >> moxParameterName )
	{
		boost::trim(moxParameterName);

		if ( moxParameterName.empty() or moxParameterName[0] == '#' )
			continue;

		subHandlers.push_back(new mox::ValueParameterHandler(processor, moxParameterName.c_str(), mox::moxNamespace));
	}
}

}
