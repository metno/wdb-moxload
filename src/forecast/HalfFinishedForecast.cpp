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

#include "HalfFinishedForecast.h"

namespace mox
{

HalfFinishedForecast::HalfFinishedForecast(const boost::shared_ptr<MoxParameterConverter> & converter) :
	converter_(converter)
{
}

HalfFinishedForecast::~HalfFinishedForecast()
{
}

Forecast HalfFinishedForecast::getForecast(const std::string & valueParameter, double value) const
{
	return Forecast(location_, analysisTime_, validFrom_, validTo_, valueParameter, value, converter_);
}

bool HalfFinishedForecast::compare::operator () (const HalfFinishedForecast & a, const HalfFinishedForecast & b) const
{
	if ( a.analysisTime() != b.analysisTime() )
		return a.analysisTime() < b.analysisTime();

	if ( a.validFrom() != b.validFrom() )
		return a.validFrom() < b.validFrom();

	if ( a.validTo() != b.validTo() )
		return a.validTo() < b.validTo();

	return a.location() < b.location();
}


}

bool operator == (const mox::HalfFinishedForecast & a, const mox::HalfFinishedForecast & b)
{
	return a.analysisTime() == b.analysisTime()
	and    a.validFrom() == b.validFrom()
	and    a.validTo() == b.validTo()
	and    a.location() == b.location();
}

