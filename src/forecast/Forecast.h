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



#ifndef FORECAST_H_
#define FORECAST_H_

#include "ForecastLocation.h"
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

class MoxParameterConverter;

namespace mox
{

class Forecast
{
public:
	typedef boost::posix_time::ptime Time;

	Forecast(const ForecastLocation & location, const Time & analysisTime,
			const Time & validFrom, const Time & validTo,
			const std::string & moxValueParameter,
			double value, boost::shared_ptr<MoxParameterConverter> converter);


	std::string getWciWriteQuery(const Time & referenceTime = Time()) const;
	std::string getLoadPlaceDefinitionQuery() const;

	bool shouldWriteToDatabase() const;

	void location(const ForecastLocation & loc) { location_ = loc; }

	// The following functions are meant for testing
	const ForecastLocation & location() const { return location_; }
	const Time & analysisTime() const { return analysisTime_; }
	const Time & validFrom() const { return validFrom_; }
	const Time & validTo() const { return validTo_; }

	const std::string wdbValueParameter() const;
	const std::string & moxValueParameter() const {  return moxValueParameter_; }
	double value() const { return value_; }
	const std::string levelParameter() const;
	double levelFrom() const;
	double levelTo() const;

private:
	ForecastLocation location_;
	Time analysisTime_;
	Time validFrom_;
	Time validTo_;
	std::string moxValueParameter_;
	double value_;
	boost::shared_ptr<MoxParameterConverter> converter_;
};

}

#endif /* FORECAST_H_ */
