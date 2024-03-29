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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Parser.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <boost/function.hpp>
#include <QXmlStreamReader>
#include <QStringRef>
#include <QString>
#include <QFile>
#include <mox/DocumentHandler.h>
#include "ForecastCollector.h"
#include "MoxParameterConverter.h"

namespace mox
{

void Parser::setup(const std::string & parameterConfigFile)
{
	std::ifstream parameters(parameterConfigFile.c_str());
	if ( ! parameters )
		throw std::runtime_error("Unable to find file: " + parameterConfigFile);
	converter_ = boost::shared_ptr<MoxParameterConverter>(new MoxParameterConverter(parameters));
}

Parser::Parser(const std::string & parameterConfigFile)
{
	setup(parameterConfigFile);
}

Parser::Parser()
{
	setup(SYSCONFDIR"/wdbFromMox.conf");
}

ForecastCollectionPtr Parser::parse(QIODevice & stream) const
{
	QXmlStreamReader reader(&stream);
	ForecastCollector collector(converter_);

	mox::DocumentHandler h(collector);
	h.handle(reader);

	return collector.forecasts();
}

ForecastCollectionPtr Parser::parseFile(const std::string & fileName) const
{
	QFile f(fileName.c_str());
	f.open(QFile::ReadOnly);
	return parse(f);
}

ForecastCollectionPtr Parser::parseStdin() const
{
	QFile f;
	f.open(0, QFile::ReadOnly);
	return parse(f);
}


}
