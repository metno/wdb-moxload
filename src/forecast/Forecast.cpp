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
		const Time & validTo, const std::string & moxValueParameter, double value,
		boost::shared_ptr<MoxParameterConverter> converter) :
	location_(location), analysisTime_(analysisTime), validFrom_(validFrom),
			validTo_(validTo), moxValueParameter_(moxValueParameter), value_(value),
			converter_(converter)
{
}

std::string Forecast::getWciWriteQuery(const Time & referenceTime) const
{
	if ( location_.locationName().empty() )
		throw std::logic_error("Write statement have no place name");

	std::ostringstream query;
	query << "SELECT wci.write(";
	query << value() << "::double precision" << sep;
	query << quote(location_.locationName()) << sep;
	if ( referenceTime.is_not_a_date_time() )
		query << quote(analysisTime()) << sep;
	else
		query << quote(referenceTime) << sep;
	query << quote(validFrom()) << sep;
	query << quote(validTo()) << sep;
	query << quote(wdbValueParameter()) << sep;
	query << quote(levelParameter()) << sep;
	query << levelFrom() << sep;
	query << levelTo() << ")";

	return query.str();
}

std::string Forecast::getLoadPlaceDefinitionQuery() const
{
	std::ostringstream query;
	query << "SELECT wci.loadPlaceDefinition(";
	query << quote(boost::to_lower_copy(location_.wellKnownText())) << sep;
	query << "geomfromtext(" << quote(location_.wellKnownText()) << ", 4030)";
	query << ")";

	return query.str();
}

bool Forecast::shouldWriteToDatabase() const
{
	return converter_->hasConversionForMoxParameter(moxValueParameter_);
}


const std::string Forecast::wdbValueParameter() const
{
	return converter_->wdbValueParameter(moxValueParameter_);
}

const std::string Forecast::levelParameter() const
{
	return converter_->wdbLevelParameter(moxValueParameter_);
}

double Forecast::levelFrom() const
{
	return converter_->levelFrom(moxValueParameter_);
}

double Forecast::levelTo() const
{
	return converter_->levelTo(moxValueParameter_);
}

}
