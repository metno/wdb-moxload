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
#include "forecast/Parser.h"
#include "configuration/MoxLoadConfiguration.h"
#include "forecast/ForecastCollectionPrinter.h"
#include "database/ForecastCollectionSaver.h"
#include <wdbLogHandler.h>
#include <QFile>
#include <pqxx/pqxx>
#include <boost/scoped_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Support Functions
namespace
{

/**
 * Write the program version to stream
 * @param	out		Stream to write to
 */
void version( ostream & out )
{
    out << PACKAGE_STRING << endl;
}

/**
 * Write help information to stram
 * @param	options		Description of the program options
 * @param	out			Stream to write to
 */
void help( const boost::program_options::options_description & options, ostream & out )
{
	version( out );
	out << '\n';
    out << "Usage: "PACKAGE_NAME" [OPTIONS] FILES...\n\n";
    out << "Options:\n";
    out << options << endl;
}
} // namespace


int main(int argc, char ** argv)
{
	MoxLoadConfiguration conf;
	try
    {
    	conf.parse( argc, argv );
    	if ( conf.general().help )
    	{
    		help( conf.shownOptions(), cout );
    		return 0;
    	}
    	if ( conf.general().version )
    	{
    		version( cout );
    		return 0;
    	}
    }
    catch( exception & e ) {
        cerr << e.what() << endl;
        help( conf.shownOptions(), clog );
        return 1;
    }

	wdb::WdbLogHandler logHandler( conf.logging().loglevel, conf.logging().logfile );
    WDB_LOG & log = WDB_LOG::getInstance( "wdb.moxLoad.main" );
    log.debug( "Starting moxLoad" );

    const std::vector<std::string> & file = conf.input().file;
	std::vector<boost::filesystem::path> files;
	copy(file.begin(), file.end(), back_inserter(files));
	if ( files.empty() )
		files.push_back("-");

	try
	{
		mox::Parser parser;

		boost::scoped_ptr<mox::ForecastHandler> forecastHandler(
				conf.output().list ?
						static_cast<mox::ForecastHandler *>(new ForecastCollectionPrinter) :
						static_cast<mox::ForecastHandler *>(new ForecastCollectionSaver(conf)));

		for ( std::vector<boost::filesystem::path>::const_iterator it = files.begin(); it != files.end(); ++ it )
		{
			mox::ForecastCollectionPtr forecasts;
			const std::string fileName = it->file_string();
			if ( fileName == "-" )
				forecasts = parser.parseStdin();
			else
				forecasts = parser.parseFile(it->file_string());

			forecastHandler->handle(forecasts);
		}
	}
	catch ( std::exception & e )
	{
		log.fatalStream() << e.what();
		return 1;
	}
}
