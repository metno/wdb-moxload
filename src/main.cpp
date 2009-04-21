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
#include "database/PointDataSaver.h"
#include <wdb/LoaderConfiguration.h>
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
	wdb::LoaderConfiguration conf("moxLoad");
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
		boost::scoped_ptr<pqxx::connection> conn(
				conf.output().list ? 0 :
				new pqxx::connection(conf.database().pqDatabaseConnection()));

		for ( std::vector<boost::filesystem::path>::const_iterator it = files.begin(); it != files.end(); ++ it )
		{
			mox::ForecastCollectionPtr forecasts;
			const std::string fileName = it->file_string();
			if ( fileName == "-" )
				forecasts = mox::parseStdin();
			else
				forecasts = mox::parseFile(it->file_string());

			if ( conf.output().list )
			{
				for (mox::ForecastCollection::const_iterator it = forecasts->begin(); it != forecasts->end(); ++ it )
					std::cout << it->getWciWriteQuery() << ";\n";
				std::cout.flush();
			}
			else
			{
				PointDataSaver s(conf.loading().dataProvider, conf.loading().loadPlaceDefinition, * forecasts);
				conn->perform(s);
			}
		}
	}
	catch ( std::exception & e )
	{
		log.fatalStream() << e.what();
		return 1;
	}
}


//			wdb::database::FeltDatabaseConnection dbConnection(conf.database().pqDatabaseConnection());
//			felt::moxLoader loader(dbConnection, conf.loading(), logHandler);
//			for ( std::vector<boost::filesystem::path>::const_iterator it = files.begin(); it != files.end(); ++ it )
//			{
//				try
//				{
//					loader.load(felt::FeltFile(*it));
//				}
//				catch ( std::exception & e )
//				{
//					log.errorStream() << "Unable to load file " << it->native_file_string();
//					log.errorStream() << "Reason: " << e.what();
//				}
//			}
