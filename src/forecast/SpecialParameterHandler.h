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

#ifndef SPECIALPARAMETERHANDLER_H_
#define SPECIALPARAMETERHANDLER_H_

#include "HalfFinishedForecast.h"
#include <string>
#include <map>
#include <set>

class DirectionalForce;
namespace mox
{
class ForecastCollector;
}


class SpecialParameterHandler
{
public:
	SpecialParameterHandler(mox::ForecastCollector & owner);
	~SpecialParameterHandler();

	bool hasSpecialHandlingFor(const std::string & moxParameterName) const;

	void handleParameter(const mox::HalfFinishedForecast & forecastStub, const std::string & valueParameter, double value);

private:
	mox::ForecastCollector & owner_;

	static std::set<std::string> specialRequirementParameters_;

	typedef std::map<std::string, double> ParameterValue;
	typedef std::map<mox::HalfFinishedForecast, ParameterValue, mox::HalfFinishedForecast::compare> WorkList;
	WorkList workList_;
};

#endif /* SPECIALPARAMETERHANDLER_H_ */
