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

#include "TagHandler.h"
#include <stdexcept>
#include <QXmlStreamReader>

#include <iostream>

namespace xml
{

TagHandler::TagHandler(const QString & tagName, const QString & tagNamespace) :
	tagName_(tagName), tagNamespace_(tagNamespace)
{
	//std::cout << "Expecting " << qPrintable(tagName_) << " in namespace " << qPrintable(tagNamespace_) << std::endl;
}

TagHandler::~TagHandler()
{
	for ( HandlerList::iterator it = subHandlers.begin(); it != subHandlers.end(); ++ it )
		delete * it;
}

bool TagHandler::matchesCurrentTag(const QXmlStreamReader & reader) const
{
	return reader.name() == tagName_ and reader.namespaceUri() == tagNamespace_;
}


void TagHandler::handle(QXmlStreamReader & reader)
{
	handleStartTag(reader);

	HandlerList::iterator nextExpectedElement = subHandlers.begin();

	while (not reader.atEnd())
	{
		QXmlStreamReader::TokenType token = reader.readNext();
		if (QXmlStreamReader::StartElement == token)
		{
			TagHandler * handler = 0;
			while ( nextExpectedElement != subHandlers.end() )
			{
				handler = * nextExpectedElement;
				if ( handler->matchesCurrentTag(reader) )
					break;
				++ nextExpectedElement;
			}

			if (nextExpectedElement == subHandlers.end())
			{
				QString msg = "\nUnexpected element:\t" + reader.name().toString() + " in namespace " + reader.namespaceUri().toString();
				msg.append('\n');
				msg.append("Allowed elements:\n");
				for ( HandlerList::const_iterator it = subHandlers.begin(); it != subHandlers.end(); ++ it )
					msg.append("\t" + (*it)->tagName_ + " in namespace "+ (*it)->tagNamespace_ + "\n");
				msg.append("Handler element:\t" + tagName_+ " in namespace " + tagNamespace_);
				throw std::logic_error(msg.toStdString());
			}
			handler->handle(reader);
		}
		else if ( QXmlStreamReader::EndElement == token )
			return;
		else if ( reader.hasError() )
			throw std::logic_error(reader.errorString().toStdString());
	}
}

void TagHandler::handleStartTag(QXmlStreamReader & reader)
{
	//std::cout << qPrintable(reader.name().toString())  << " - " << typeid(* this).name() << std::endl;
}


}
