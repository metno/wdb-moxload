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
#include <util/timeConversion.h>
#include <boost/lexical_cast.hpp>
#include <set>

PointDataSaver::PointDataSaver(const std::string & referenceTime, const std::string & dataProvider, bool loadPlaceDefinition, const mox::ForecastCollection & forecasts) :
	pqxx::transactor<>("PointDataSaver"), dataProvider_(dataProvider), loadPlaceDefinition_(loadPlaceDefinition), forecasts_(forecasts)
{
	if ( not referenceTime.empty() )
	{
		try
		{
			referenceTime_ = getPtime(referenceTime);
		}
		catch ( std::exception & )
		{
			throw std::logic_error("Invalid reference time specification: " + referenceTime);
		}
	}
}

PointDataSaver::~PointDataSaver()
{
}

void PointDataSaver::operator()(PointDataSaver::argument_type & t)
{
	t.exec("SELECT wci.begin('" + dataProvider_ + "')");

	for ( mox::ForecastCollection::const_iterator it = forecasts_.begin(); it != forecasts_.end(); ++ it )
	{
		if ( it->shouldWriteToDatabase() )
		{
			mox::Forecast f = * it;

			const ForecastLocation & location = verifyPlaceDefinition(t, f);
			f.location(location);
			//std::cout << f.getWciWriteQuery(referenceTime_) << std::endl;
			t.exec(f.getWciWriteQuery(referenceTime_));
		}
		else
			std::cout << "Skipping " << it->moxValueParameter() << std::endl;
	}
	t.exec("SELECT wci.end()");
}

const ForecastLocation & PointDataSaver::verifyPlaceDefinition(PointDataSaver::argument_type & t, const mox::Forecast & forecast)
{
	// Used to prevent doing a lookup of the same location several times
	typedef std::set<ForecastLocation> LocationCache;
	static LocationCache locationCache;

	std::set<ForecastLocation>::const_iterator find = locationCache.find(forecast.location());
	if ( find == locationCache.end() )
	{
		ForecastLocation location = forecast.location(); // copy

		const std::string query = "SELECT placename FROM  wci.info(NULL, NULL::wci.infoplace) WHERE astext(placegeometry)='" + location.wellKnownText() + "'";
		pqxx::result r = t.exec(query);
		if ( r.empty() )
		{
			if ( loadPlaceDefinition_ )
			{
				t.exec(forecast.getLoadPlaceDefinitionQuery());
				location.locationName(location.getDefaultLocationName());
			}
			else
				throw std::logic_error("Unknown location: " + location.wellKnownText());
		}
		else
		{
			location.locationName(r[0][0].as<std::string>());
			std::cout << "Got location in database: " << location.wellKnownText() << ", name " << location.locationName() << std::endl;
		}
		std::pair<LocationCache::iterator,bool> insert = locationCache.insert(location);
		find = insert.first;
	}
	return * find;
}
