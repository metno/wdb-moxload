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

#ifndef MOX_PARSER_H_
#define MOX_PARSER_H_

#include "ForecastCollection.h"
#include <boost/shared_ptr.hpp>
#include <string>

class QIODevice;
class MoxParameterConverter;

namespace mox
{

class Parser
{
public:
	Parser();
	explicit Parser(const std::string & parameterConfigFile);

	ForecastCollectionPtr parse(QIODevice & stream) const;

	ForecastCollectionPtr parseFile(const std::string & fileName) const;

	ForecastCollectionPtr parseStdin() const;

private:
	void setup(const std::string & parameterConfigFile);

	boost::shared_ptr<MoxParameterConverter> converter_;
};

}

#endif /* MOX_PARSER_H_ */
