/*
 * ForecastCollector.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: vegardb
 */

#include "ForecastCollector.h"
#include "DirectionalForce.h"
#include <QXmlStreamReader>
#include <iostream>
#include <cmath>

namespace mox
{

ForecastCollector::ForecastCollector(boost::shared_ptr<MoxParameterConverter> converter) :
	currentWork_(converter),
	forecasts_(new ForecastCollection),
	specialParameterHandler_(* this)
{
}

ForecastCollector::~ForecastCollector()
{
}

void ForecastCollector::setLocation(const ForecastLocation & location)
{
	currentWork_.location(location);
}

void ForecastCollector::setAnalysisTime(const Forecast::Time & time)
{
	currentWork_.analysisTime(time);
}

void ForecastCollector::setValidFrom(const Forecast::Time & time)
{
	currentWork_.validFrom(time);
}

void ForecastCollector::setValidTo(const Forecast::Time & time)
{
	currentWork_.validTo(time);
}

void ForecastCollector::setValue(const std::string & valueParameter, double value)
{
	if ( specialParameterHandler_.hasSpecialHandlingFor(valueParameter) )
		specialParameterHandler_.handleParameter(currentWork_, valueParameter, value);
	else
	{
		Forecast f = currentWork_.getForecast(valueParameter, value);
		forecasts_->push_back(f);
	}
}


}
