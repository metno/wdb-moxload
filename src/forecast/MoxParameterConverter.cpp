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

#include "MoxParameterConverter.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <functional>
#include <iostream>

MoxParameterConverter::MoxParameterConverter(std::istream & conversionFile)
{
	std::string line;
	while ( std::getline(conversionFile, line) )
	{
		//void parseParameterConversionLine(const std::string conversionLine, std::string & moxParameterNameOut, WdbParameter & out)

		std::string moxName;
		WdbParameter wdbParam;
		parseParameterConversionLine(line, moxName, wdbParam);
		if ( not moxName.empty() )
			conversion_[moxName] = wdbParam;
	}
}

MoxParameterConverter::~MoxParameterConverter()
{
}

bool MoxParameterConverter::hasConversionForMoxParameter(const std::string & moxValueParameter) const
{
	return conversion_.find(moxValueParameter) != conversion_.end();
}


std::string MoxParameterConverter::wdbValueParameter(const std::string & moxValueParameter) const
{
	return getParameter_(moxValueParameter).valueParameter;
}

std::string MoxParameterConverter::wdbLevelParameter(const std::string & moxValueParameter) const
{
	return getParameter_(moxValueParameter).levelParameter;
}

double MoxParameterConverter::levelFrom(const std::string & moxValueParameter) const
{
	return getParameter_(moxValueParameter).levelFrom;
}

double MoxParameterConverter::levelTo(const std::string & moxValueParameter) const
{
	return getParameter_(moxValueParameter).levelTo;
}

const WdbParameter & MoxParameterConverter::getParameter_(const std::string & moxValueParameter) const
{
	ParameterConversionMap::const_iterator f = conversion_.find(moxValueParameter);

	if ( conversion_.end() == f )
		throw std::runtime_error("Unknown mox value parameter: " + moxValueParameter);

	return f->second;
}

void parseParameterConversionLine(const std::string conversionLine, std::string & moxParameterNameOut, WdbParameter & out)
{
	std::vector<std::string> elements;
	boost::split(elements, conversionLine, boost::is_any_of("="));
	for ( std::vector<std::string>::iterator it = elements.begin(); it != elements.end(); ++ it )
		boost::trim(* it);

	if ( elements.size() == 1 )
	{
		if ( elements[0].empty() )
			return;
		else throw std::runtime_error("Invalid line: " + conversionLine);
	}
	if ( elements.size() == 2 )
	{
		parse(elements[1], out);
		moxParameterNameOut = elements[0];
	}
	else
		throw std::runtime_error("Invalid line: " + conversionLine);
}

void parse(const std::string & moxParameter, WdbParameter & out)
{
	std::vector<std::string> elements;
	boost::split(elements, moxParameter, boost::is_any_of(","));
	for ( std::vector<std::string>::iterator it = elements.begin(); it != elements.end(); ++ it )
		boost::trim(* it);

	if ( elements.size() != 4 )
		throw std::runtime_error("Invalid parameter spec: " + moxParameter);

	out.valueParameter = elements[0];
	try
	{
		out.levelFrom = boost::lexical_cast<double>(elements[1]);
		out.levelTo = boost::lexical_cast<double>(elements[2]);
	}
	catch( boost::bad_lexical_cast & )
	{
		throw std::runtime_error("Invalid parameter spec: " + moxParameter);
	}
	out.levelParameter = elements[3];
}
