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

#include "Forecast.h"
#include "MoxParameterConverter.h"
#include <sstream>

namespace mox
{
namespace
{
/// get the separator between arguments in an sql query
const std::string sep = ", ";

template<typename T>
std::string quote(const T & t)
{
	std::ostringstream s;
	s << '\'' << t << '\'';
	return s.str();
}

std::string location(double latitude, double longitude)
{
	std::ostringstream s;
	s << "POINT(" << latitude << ' ' << longitude << ")";
	return s.str();
}
}

Forecast::Forecast(const ForecastLocation & location,
		const Time & analysisTime, const Time & validFrom,
		const Time & validTo, const std::string & valueParameter, double value,
		boost::shared_ptr<MoxParameterConverter> converter) :
	location_(location), analysisTime_(analysisTime), validFrom_(validFrom),
			validTo_(validTo), valueParameter_(valueParameter), value_(value),
			converter_(converter)
{
}

std::string Forecast::getWciWriteQuery() const
{
	//	wci.write(
	//		value_ 			oid,
	//		placename_ 		text,
	//		referencetime_ 	timestamp with time zone,
	//		validFrom_ 		timestamp with time zone,
	//		validTo_ 		timestamp with time zone,
	//		valueparameter_ text,
	//		levelparameter_ text,
	//		levelFrom_ 		real,
	//		levelTo_ 		real
	//	)
	std::ostringstream query;
	query << "SELECT wci.write(";
	query << value() << "::double precision" << sep;
	query << quote(location_.locationName()) << sep;
	query << quote(analysisTime()) << sep;
	query << quote(validFrom()) << sep;
	query << quote(validTo()) << sep;
	query << quote(valueParameter()) << sep;
	query << quote(levelParameter()) << sep;
	query << levelFrom() << sep;
	query << levelTo() << ")";

	return query.str();
}

std::string Forecast::getLoadPlaceDefinitionQuery() const
{
	std::ostringstream query;
	query << "SELECT wci.loadPlaceDefinition(";
	query << quote(location_.locationName()) << sep;
	query << "geomfromtext('POINT(" << location_.latitude() << ' ' << location_.longitude() << ")', 4030)";
	query << ")";

	return query.str();
}

const std::string Forecast::valueParameter() const
{
	return converter_->wdbValueParameter(valueParameter_);
}

const std::string Forecast::levelParameter() const
{
	return converter_->wdbLevelParameter(valueParameter_);
}

double Forecast::levelFrom() const
{
	return converter_->levelFrom(valueParameter_);
}

double Forecast::levelTo() const
{
	return converter_->levelTo(valueParameter_);
}

}
