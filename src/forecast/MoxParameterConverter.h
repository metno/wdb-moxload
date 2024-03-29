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

#ifndef MOXMoxParameterConverter_H_
#define MOXMoxParameterConverter_H_

#include <string>
#include <iosfwd>
#include <map>

struct WdbParameter;

class MoxParameterConverter
{
public:
	MoxParameterConverter(std::istream & conversionFile);
	virtual ~MoxParameterConverter();

	bool hasConversionForMoxParameter(const std::string & moxValueParameter) const;

	std::string wdbValueParameter(const std::string & moxValueParameter) const;
	std::string wdbLevelParameter(const std::string & moxValueParameter) const;
	double levelFrom(const std::string & moxValueParameter) const;
	double levelTo(const std::string & moxValueParameter) const;

private:
	const WdbParameter & getParameter_(const std::string & moxValueParameter) const;

	typedef std::map<std::string, WdbParameter> ParameterConversionMap;
	ParameterConversionMap conversion_;
};

struct WdbParameter
{
	std::string valueParameter;
	double levelFrom;
	double levelTo;
	std::string levelParameter;
};

void parseParameterConversionLine(const std::string conversionLine, std::string & moxParameterNameOut, WdbParameter & out);
void parse(const std::string & moxParameter, WdbParameter & out);

#endif /* MOXMoxParameterConverter_H_ */
