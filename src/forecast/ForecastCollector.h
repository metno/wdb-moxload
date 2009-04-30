/*
 * ForecastCollector.h
 *
 *  Created on: Apr 1, 2009
 *      Author: vegardb
 */

#ifndef FORECASTCOLLECTOR_H_
#define FORECASTCOLLECTOR_H_

#include "ForecastCollection.h"
#include "SpecialParameterHandler.h"
#include "HalfFinishedForecast.h"
#include <boost/noncopyable.hpp>
#include <string>


namespace mox
{

class ForecastCollector : boost::noncopyable
{
public:
	explicit ForecastCollector(boost::shared_ptr<MoxParameterConverter> converter);
	~ForecastCollector();

	void setLocation(const ForecastLocation & locaion);
	void setAnalysisTime(const Forecast::Time & time);
	void setValidFrom(const Forecast::Time & time);
	void setValidTo(const Forecast::Time & time);
	void setValue(const std::string & valueParameter, double value);

	const ForecastCollectionPtr forecasts() const { return forecasts_; }

	ForecastLocation & location() { return currentWork_.location(); }

	// The following functions are for testing purposes
	const ForecastLocation & location() const { return currentWork_.location(); }
	const Forecast::Time & validFrom() const { return currentWork_.validFrom(); }
	const Forecast::Time & validTo() const { return currentWork_.validTo(); }

private:
	HalfFinishedForecast currentWork_;

	ForecastCollectionPtr forecasts_;

	SpecialParameterHandler specialParameterHandler_;
};

}

#endif /* FORECASTCOLLECTOR_H_ */
