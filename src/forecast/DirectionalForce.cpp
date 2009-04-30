/*
 moxLoad

 Copyright (C) 2008 met.no

 Contact information:
 Norwegian Meteorological Institute
 Box 43 Blindern
 0313 OSLO
 NORWAY
 E-mail: probabilityForecast@met.no

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

#include "DirectionalForce.h"
#include <cmath>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <cmath>
#include <limits>

DirectionalForce::DirectionalForce()
	: u_(std::numeric_limits<double>::quiet_NaN()), v_(std::numeric_limits<double>::quiet_NaN())
{}

DirectionalForce::DirectionalForce(double u, double v)
	: u_(u), v_(v)
{}

DirectionalForce::DirectionalForce(DirectionalForce::Direction direction, double force)
{
	u_ = sin(direction.radians()) * force;
	v_ = cos(direction.radians()) * force;
}

DirectionalForce::~DirectionalForce()
{}

double DirectionalForce::force() const
{
	return std::sqrt((u_*u_) + (v_*v_));
}

DirectionalForce::Direction DirectionalForce::direction() const
{
	const double radiansToDegrees = 180 / M_PIl;
	double ret = (std::atan2(v_, u_) * radiansToDegrees) /*+ 180*/;
	return Direction(ret);
}


DirectionalForce::Direction::Direction(double dir)
	: dir_(dir)
{
	while ( dir_ <= -180 )
		dir_ += 360;
	while ( 180 < dir_ )
		dir_ -= 360;
}

double DirectionalForce::Direction::differenceTo(DirectionalForce::Direction d) const
{
	double a = dir_;
	double b = double(d);
	return DirectionalForce::Direction(a - b);
}

DirectionalForce DirectionalForce::scaledTo(double windForce) const
{
	double factor = windForce / force();

	return DirectionalForce(u_ * factor, v_ * factor);
}

struct makeWind : std::binary_function<double, double, DirectionalForce>
{
	DirectionalForce operator () (double u, double v) const
	{
		return DirectionalForce(u, v);
	}
};


