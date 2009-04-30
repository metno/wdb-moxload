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

#ifndef HALFFINISHEDFORECAST_H_
#define HALFFINISHEDFORECAST_H_

#include "Forecast.h"
#include <string>

namespace mox
{

class HalfFinishedForecast
{
public:
	HalfFinishedForecast(const boost::shared_ptr<MoxParameterConverter> & converter);
	~HalfFinishedForecast();

	void location(const ForecastLocation & location) { location_ = location; }
	void analysisTime(const Forecast::Time & time) { analysisTime_ = time; }
	void validFrom(const Forecast::Time & time) { validFrom_ = time; }
	void validTo(const Forecast::Time & time) { validTo_ = time; }

	Forecast getForecast(const std::string & valueParameter, double value) const;

	ForecastLocation & location() { return location_; }

	const ForecastLocation & location() const { return location_; }
	const Forecast::Time & analysisTime() const { return analysisTime_; }
	const Forecast::Time & validFrom() const { return validFrom_; }
	const Forecast::Time & validTo() const { return validTo_; }

	struct compare;

private:
	boost::shared_ptr<MoxParameterConverter> converter_;
	ForecastLocation location_;
	Forecast::Time analysisTime_;
	Forecast::Time validFrom_;
	Forecast::Time validTo_;
};

/// Compare two HalfFinishedForecast, for insertion into maps and such
struct HalfFinishedForecast::compare : public std::binary_function<HalfFinishedForecast,HalfFinishedForecast,bool>
{
	bool operator () (const HalfFinishedForecast & a, const HalfFinishedForecast & b) const;
};

}

bool operator == (const mox::HalfFinishedForecast & a, const mox::HalfFinishedForecast & b);
inline bool operator != (const mox::HalfFinishedForecast & a, const mox::HalfFinishedForecast & b)
{
	return ! operator == (a,b);
}

#endif /* HALFFINISHEDFORECAST_H_ */
