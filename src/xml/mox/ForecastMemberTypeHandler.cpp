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

#include "ForecastMemberTypeHandler.h"
#include "ForecastTypeHandler.h"
//#include <metno/LocationForecastHandler.h>
//#include <metno/OceanForecastHandler.h>
#include "namespace.h"
#include <configuration/configFileLookup.h>
#include <metno/namespace.h>

namespace mox
{

ForecastMemberTypeHandler::ForecastMemberTypeHandler(ForecastCollector & processor, const QString & tagName, const QString & tagNamespace) :
	MoxTagHandler(processor, tagName, tagNamespace)
{
}

void ForecastMemberTypeHandler::addSubHandlers()
{
	MoxTagHandler::addSubHandlers();

	subHandlers.push_back(new ForecastTypeHandler(collector, "LocationForecast", metno::metnoNamespace, getConfigFile("LocationForecast.conf").file_string()));
	subHandlers.push_back(new ForecastTypeHandler(collector, "OceanForecast", metno::metnoNamespace, getConfigFile("OceanForecast.conf").file_string()));
}

}
