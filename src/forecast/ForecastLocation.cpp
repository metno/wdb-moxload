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

#include "ForecastLocation.h"
#include <boost/static_assert.hpp>
#include <boost/algorithm/string.hpp>
#include <limits>
#include <sstream>

ForecastLocation::ForecastLocation() :
	latitude_(std::numeric_limits<double>::quiet_NaN()), longitude_(std::numeric_limits<double>::quiet_NaN())
{
}

ForecastLocation::ForecastLocation(const std::string & locationName) :
	locationName_(locationName), latitude_(std::numeric_limits<double>::quiet_NaN()), longitude_(std::numeric_limits<double>::quiet_NaN())
{
}


ForecastLocation::ForecastLocation(	const std::string & locationName, double latitude, double longitude) :
	locationName_(locationName), latitude_(latitude), longitude_(longitude)
{
}

ForecastLocation::~ForecastLocation()
{
}

std::string ForecastLocation::getDefaultLocationName() const
{
	return boost::to_lower_copy(wellKnownText());
}

std::string ForecastLocation::wellKnownText() const
{
	std::ostringstream wkt;
	wkt << "POINT(" << latitude() << ' ' << longitude() << ")";
	return wkt.str();
}


bool operator < (const ForecastLocation & a, const ForecastLocation & b)
{
//	if ( a.locationName() != b.locationName() )
//		return a.locationName() < b.locationName();
	if ( a.latitude() != b.latitude() )
		return a.latitude() < b.latitude();
	return a.longitude() < b.longitude();
}

bool operator == (const ForecastLocation & a, const ForecastLocation & b)
{
	return //a.locationName() == b.locationName()	and
	a.latitude() == b.latitude() and
	a.longitude() == b.longitude();
}



BOOST_STATIC_ASSERT( std::numeric_limits<double>::has_quiet_NaN );
