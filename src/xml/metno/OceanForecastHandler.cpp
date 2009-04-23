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

#include "OceanForecastHandler.h"
#include "namespace.h"
#include <mox/ValueParameterHandler.h>
#include <mox/namespace.h>


namespace metno
{

OceanForecastHandler::OceanForecastHandler(mox::ForecastCollector & processor) :
	mox::ForecastTypeHandler(processor, "OceanForecast", metnoNamespace)
{
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "seaIcePresence", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "meanTotalWaveDirection", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "peakTotalWaveDirection", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "significantTotalWaveHeight", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "seaCurrentDirection", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "seaCurrentSpeed", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "seaSurfaceHeight", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "seaTemperature", mox::moxNamespace));

	/* Correct order:
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "airPressure", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "airTemperature", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "precipitation", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "seaBottomTopography", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "seaCurrentDirection", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "seaCurrentSpeed", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "seaIcePresence", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "seaSalinity", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "seaSurfaceHeight", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "seaTemperature", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "meanTotalWaveDirection", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "peakTotalWaveDirection", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "significantTotalWaveHeight", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "windDirection", mox::moxNamespace));
	subHandlers.push_back(new mox::ValueParameterHandler(processor, "windSpeed", mox::moxNamespace));
	*/
}


}
