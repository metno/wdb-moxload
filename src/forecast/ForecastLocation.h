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

#ifndef FORECASTLOCATION_H_
#define FORECASTLOCATION_H_

#include <string>

class ForecastLocation
{
public:
	ForecastLocation();
	ForecastLocation(const std::string & locationName);
	ForecastLocation(const std::string & locationName, double latitude, double longitude);
	~ForecastLocation();


	std::string getDefaultLocationName() const;
	const std::string & locationName() const { return locationName_; }
	double latitude() const { return latitude_; }
	double longitude() const { return longitude_; }

	void locationName(const std::string & name) { locationName_ = name; }
	void latitude(double lat) { latitude_ = lat; }
	void longitude(double lon) { longitude_ = lon; }

	std::string wellKnownText() const;

private:
	std::string locationName_;
	double latitude_;
	double longitude_;
};

/// Comparison, for sorting
bool operator < (const ForecastLocation & a, const ForecastLocation & b);
bool operator == (const ForecastLocation & a, const ForecastLocation & b);

#endif /* FORECASTLOCATION_H_ */
