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

#ifndef DIRECTIONALFORCE_H_
#define DIRECTIONALFORCE_H_

#include <cmath>
#include <ostream>

/**
 * A single representation of U- and V components of DirectionalForce, along with various
 * functions to do Directional Force math
 */
class DirectionalForce
{
public:
	class Direction;

	DirectionalForce();
	DirectionalForce(double u, double v);
	DirectionalForce(Direction direction, double force);
	~DirectionalForce();

	/// DirectionalForce direction, in degrees
	class Direction
	{
	public:
		explicit Direction(double dir);

		double differenceTo(Direction d) const;

		operator double () const { return dir_; }

		double radians() const { return dir_ * (M_PIl/180); }
	private:
		double dir_;
	};

	double force() const;

	/// DirectionalForce direction, in degrees
	Direction direction() const;

	double u() const { return u_; }
	double v() const { return v_; }

	DirectionalForce scaledTo(double windForce) const;

private:
	double u_;
	double v_;
};

inline bool operator == (const DirectionalForce & a, const DirectionalForce & b)
{
	return std::abs(a.u()-b.u()) < 0.0001 and std::abs(a.v()-b.v()) < 0.0001;
}

inline std::ostream & operator << (std::ostream & s, const DirectionalForce & w)
{
	return s << "DirectionalForce(" << w.u() << ',' << w.v() << ')';
}

#endif /* DIRECTIONALFORCE_H_ */
