/*
 * MoxTagHandler.h
 *
 *  Created on: Apr 3, 2009
 *      Author: vegardb
 */

#ifndef MOXTAGHANDLER_H_
#define MOXTAGHANDLER_H_

#include <xml/TagHandler.h>

namespace mox
{

class ForecastCollector;

class MoxTagHandler: public xml::TagHandler
{
public:
	MoxTagHandler(ForecastCollector & collector, const QString & tagName, const QString & tagNamespace);
	virtual ~MoxTagHandler();

protected:
//	virtual void handleStartTag(QXmlStreamReader & reader);

	ForecastCollector & collector;
};

}

#endif /* MOXTAGHANDLER_H_ */
