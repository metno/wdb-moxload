/*
 * ForecastCollection.h
 *
 *  Created on: Apr 1, 2009
 *      Author: vegardb
 */

#ifndef FORECASTCOLLECTION_H_
#define FORECASTCOLLECTION_H_


#include "Forecast.h"
#include <boost/shared_ptr.hpp>
#include <vector>

namespace mox
{

typedef std::vector<Forecast> ForecastCollection;
typedef boost::shared_ptr<ForecastCollection> ForecastCollectionPtr;

}

#endif /* FORECASTCOLLECTION_H_ */
