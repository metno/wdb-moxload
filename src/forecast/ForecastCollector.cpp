/*
 * ForecastCollector.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: vegardb
 */

#include "ForecastCollector.h"
#include <iostream>
#include <QXmlStreamReader>

namespace mox
{

ForecastCollector::ForecastCollector(boost::shared_ptr<MoxParameterConverter> converter) :
	validFrom_(boost::posix_time::time_from_string("2009-02-10 12:00:00")),
	forecasts_(new ForecastCollection),
	converter_(converter)
{
}

void ForecastCollector::setLocation(const ForecastLocation & location)
{
	location_ = location;
}

void ForecastCollector::setAnalysisTime(const Forecast::Time & time)
{
	analysisTime_ = time;
}

void ForecastCollector::setValidFrom(const Forecast::Time & time)
{
	validFrom_ = time;
}

void ForecastCollector::setValidTo(const Forecast::Time & time)
{
	validTo_ = time;
}

void ForecastCollector::setValue(const std::string & valueParameter, double value)
{
	Forecast f(location_, analysisTime_, validFrom_, validTo_, valueParameter, value, converter_);
	forecasts_->push_back(f);
}


}
