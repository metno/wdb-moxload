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

#include "TimePrimitivePropertyTypeHandler.h"
#include "TimeInstantHandler.h"
#include "TimePeriodHandler.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gml
{


TimePrimitivePropertyTypeHandler::TimePrimitivePropertyTypeHandler(mox::ForecastCollector & processor, const QString & tagName, const QString & tagNamespace) :
	mox::MoxTagHandler(processor, tagName, tagNamespace),
	instantHandler(new TimeInstantHandler(processor)),
	periodHandler(new TimePeriodHandler(processor))
{}

void TimePrimitivePropertyTypeHandler::addSubHandlers()
{
	MoxTagHandler::addSubHandlers();

	subHandlers.push_back(instantHandler);
	subHandlers.push_back(periodHandler);
}

const boost::posix_time::ptime & TimePrimitivePropertyTypeHandler::timeFrom() const
{
	if ( not instantHandler->timeInstant().is_not_a_date_time() )
		return instantHandler->timeInstant();
	return periodHandler->from();
}

const boost::posix_time::ptime & TimePrimitivePropertyTypeHandler::timeTo() const
{
	if ( not instantHandler->timeInstant().is_not_a_date_time() )
		return instantHandler->timeInstant();
	return periodHandler->to();
}

}
