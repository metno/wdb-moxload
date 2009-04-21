/*
 * ForecastCollector.h
 *
 *  Created on: Apr 1, 2009
 *      Author: vegardb
 */

#ifndef FORECASTCOLLECTOR_H_
#define FORECASTCOLLECTOR_H_

#include "ForecastCollection.h"
#include <boost/noncopyable.hpp>
#include <string>

namespace mox
{

class ForecastCollector : boost::noncopyable
{
public:
	explicit ForecastCollector(boost::shared_ptr<MoxParameterConverter> converter);

	void setLocation(const ForecastLocation & locaion);
	void setAnalysisTime(const Forecast::Time & time);
	void setValidFrom(const Forecast::Time & time);
	void setValidTo(const Forecast::Time & time);
	void setValue(const std::string & valueParameter, double value);

	const ForecastCollectionPtr forecasts() const { return forecasts_; }

	ForecastLocation & location() { return location_; }

	// The following functions are for testing purposes
	const ForecastLocation & location() const { return location_; }
	const Forecast::Time & validFrom() const { return validFrom_; }
	const Forecast::Time & validTo() const { return validTo_; }

private:
	ForecastLocation location_;
	Forecast::Time analysisTime_;
	Forecast::Time validFrom_;
	Forecast::Time validTo_;

	ForecastCollectionPtr forecasts_;

	boost::shared_ptr<MoxParameterConverter> converter_;
};

}

#endif /* FORECASTCOLLECTOR_H_ */
