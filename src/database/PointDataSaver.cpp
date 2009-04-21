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

#include "PointDataSaver.h"
#include <boost/lexical_cast.hpp>
#include <set>

PointDataSaver::PointDataSaver(const std::string & dataProvider, bool loadPlaceDefinition, const mox::ForecastCollection & forecasts) :
	pqxx::transactor<>("PointDataSaver"), dataProvider_(dataProvider), loadPlaceDefinition_(loadPlaceDefinition), forecasts_(forecasts)
{
}

PointDataSaver::~PointDataSaver()
{
}

void PointDataSaver::operator()(PointDataSaver::argument_type & t)
{
	t.exec("SELECT wci.begin('" + dataProvider_ + "')");

	for ( mox::ForecastCollection::const_iterator it = forecasts_.begin(); it != forecasts_.end(); ++ it )
	{
		verifyPlaceDefinition(t, * it);

		t.exec(it->getWciWriteQuery());
	}
	t.exec("SELECT wci.end()");
}

void PointDataSaver::verifyPlaceDefinition(PointDataSaver::argument_type & t, const mox::Forecast & forecast)
{
	// Used to prevent doing a lookup of the same location several times
	static std::set<ForecastLocation> locationCache;

	const ForecastLocation & location = forecast.location();

	if ( locationCache.find(location) == locationCache.end() )
	{
		pqxx::result r = t.exec("SELECT placename, astext(placegeometry) FROM  wci.info('" + location.locationName() + "', NULL::wci.infoplace)");
		if ( r.empty() )
		{
			if ( loadPlaceDefinition_ )
				t.exec(forecast.getLoadPlaceDefinitionQuery());
			else
				throw std::logic_error("Unknown location: " + location.locationName() + " at " + location.wellKnownText());
		}
		else
		{
			const std::string storedLocation = r[0][1].as<std::string>();
			if ( location.wellKnownText() != storedLocation )
			{
				std::ostringstream msg;
				msg << "Database already havea location called <" << location.locationName() << "> with  geometry " << r[0][1] << ". ";
				msg << "This does not match the given location of " << location.wellKnownText();
				throw std::logic_error(msg.str());
			}
		}
		locationCache.insert(location);
	}
}
