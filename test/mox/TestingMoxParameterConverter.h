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



#ifndef TESTINGMOXPARAMETERCONVERTER_H_
#define TESTINGMOXPARAMETERCONVERTER_H_

#include <forecast/MoxParameterConverter.h>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <stdexcept>

inline boost::shared_ptr<MoxParameterConverter> & getConverter()
{
	static boost::shared_ptr<MoxParameterConverter> converter;
	if ( ! converter )
	{
		std::ifstream params(TEST_CONFIG_LOCATION"/etc/wdbFromMox.conf");
		if ( ! params )
			throw std::runtime_error("Unable to find file: "TEST_CONFIG_LOCATION"/etc/wdbFromMox.conf");
		converter = boost::shared_ptr<MoxParameterConverter>(new MoxParameterConverter(params));
	}
	return converter;
}


#endif /* TESTINGMOXPARAMETERCONVERTER_H_ */
