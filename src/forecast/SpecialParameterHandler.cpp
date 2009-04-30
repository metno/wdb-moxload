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

#include "SpecialParameterHandler.h"
#include "ForecastCollector.h"
#include "DirectionalForce.h"
#include "HalfFinishedForecast.h"
#include <boost/assign/std/set.hpp>
#include <iostream>

using namespace std;
using namespace mox;
using namespace boost::assign;

std::set<std::string> SpecialParameterHandler::specialRequirementParameters_;

SpecialParameterHandler::SpecialParameterHandler(ForecastCollector & owner) :
	owner_(owner)
{
	if ( specialRequirementParameters_.empty() )
		specialRequirementParameters_ += "seaCurrentDirection",	"seaCurrentSpeed";
}

SpecialParameterHandler::~SpecialParameterHandler()
{
}

bool SpecialParameterHandler::hasSpecialHandlingFor(const std::string & moxParameterName) const
{
	return specialRequirementParameters_.find(moxParameterName) != specialRequirementParameters_.end();
}

void SpecialParameterHandler::handleParameter(const mox::HalfFinishedForecast & forecastStub, const std::string & valueParameter, double value)
{
	ParameterValue & params = workList_[forecastStub];
	params[valueParameter] = value;

	ParameterValue::const_iterator seaCurrentDirection = params.find("seaCurrentDirection");
	ParameterValue::const_iterator seaCurrentSpeed = params.find("seaCurrentSpeed");
	if ( seaCurrentDirection != params.end() and seaCurrentSpeed != params.end() )
	{
		DirectionalForce df(DirectionalForce::Direction(seaCurrentDirection->second), seaCurrentSpeed->second);

		owner_.setValue("seaCurrentVelocityU", df.u());
		owner_.setValue("seaCurrentVelocityV", df.v());
	}
}
