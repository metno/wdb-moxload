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

#ifndef ABSTRACTGMLTYPEHANDLER_H_
#define ABSTRACTGMLTYPEHANDLER_H_

#include <xml/TagHandler.h>

namespace gml
{

/**
 * Defines subtags that all gml tags may have.
 *
 * @note this is not a (C++) abstract class. The class name refers to an xml
 * element type. Therefore you may instantiate this class to create an element
 * handler which ignores  its subelements
 */
class AbstractGmlTypeHandler : public xml::TagHandler
{
public:
	AbstractGmlTypeHandler(const QString & tagName, const QString & tagNamespace);

protected:
	virtual void handleStartTag(QXmlStreamReader & reader);
};

}

#endif /* ABSTRACTGMLTYPEHANDLER_H_ */
