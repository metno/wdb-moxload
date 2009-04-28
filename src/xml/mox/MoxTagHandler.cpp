/*
 * MoxTagHandler.cpp
 *
 *  Created on: Apr 3, 2009
 *      Author: vegardb
 */

#include "MoxTagHandler.h"
#include <forecast/ForecastCollector.h>

namespace mox
{

MoxTagHandler::MoxTagHandler(ForecastCollector & collector, const QString & tagName, const QString & tagNamespace)
	: gml::AbstractGmlTypeHandler(tagName, tagNamespace), collector(collector)
{
}

MoxTagHandler::~MoxTagHandler()
{
}

}
