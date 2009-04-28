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

#ifndef TAGHANDLER_H_
#define TAGHANDLER_H_

#include <QString>
#include <boost/noncopyable.hpp>
#include <deque>

class QXmlStreamReader;

namespace xml
{

/**
 * Handler for a specific tag in an xml document. You may overrride this
 * class' processTag function to do any acion when encountering the given tag.
 * Sub tags are handled by populating the subHandlers list with other tag
 * handler objects.
 */
class TagHandler : boost::noncopyable
{
public:
	/**
	 * @param tagName name of the tag to be processed
	 * @param tagNamespace namespace of the tag, if applicable. Use URI namespaces, not aliases.
	 */
	TagHandler(const QString & tagName, const QString & tagNamespace);
	virtual ~TagHandler();

	/// Should the just read tag from the giver reader be handled by this object?
	virtual bool matchesCurrentTag(const QXmlStreamReader & reader) const;

	/// Handle  the just read tag, possibly by reading more from the document
	virtual void handle(QXmlStreamReader & reader);

protected:

	/// Override to handle encounter of start tag
	virtual void handleStartTag(QXmlStreamReader & reader);
	virtual void addSubHandlers();

	typedef std::deque<TagHandler *> HandlerList;

	/// List of handlers for all allowed sub-elements of this handler
	HandlerList subHandlers;

private:
	void setSubHandlers_();

	const QString tagName_;
	const QString tagNamespace_;
	bool hasSetSubHandlers_;
};

}

#endif /* TAGHANDLER_H_ */
