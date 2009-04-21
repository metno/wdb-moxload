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

#include "LocationForecastHandler.h"
#include "namespace.h"
#include <mox/ValueParameterHandler.h>
#include <mox/namespace.h>

namespace metno
{

LocationForecastHandler::LocationForecastHandler(mox::ForecastCollector & processor) :
	mox::ForecastTypeHandler(processor, "LocationForecast", metnoNamespace)
{
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "airPressure", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "airTemperature", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "totalCloudCover", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "lowCloudCover", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "mediumCloudCover", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "highCloudCover", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "fogCover", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "humidity", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "precipitation", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "windDirection", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "windSpeed", mox::moxNamespace));
}


}
