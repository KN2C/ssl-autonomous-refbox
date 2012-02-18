#include "global.h"
#include "../ConfigFile/ConfigFile.h"
#include <iostream>
#include <stdlib.h>

using namespace log4cxx;
using namespace log4cxx::helpers;
using namespace std;

// name logger is used in another class :o don't know why...
LoggerPtr logger42 ( Logger::getLogger ( "Global" ) );

ConfigFile Global::config; //( configFile );

void Global::loadConfig()
{
    string configFile = "ssl-autonomous-refbox.conf";
    string home = getenv ( "HOME" );
    if ( home.empty() ) {
        home = "/root";
    }
    string configPath[] = {configFile,
                           "/etc/" + configFile,
                           home + "/.ssl-autonomous-refbox/" + configFile
                          };

    for ( int i=0; i<3; i++ ) {
        std::ifstream in ( configPath[i].c_str() );
        if ( in ) {
            in >> Global::config;
            LOG4CXX_INFO ( logger42, "ConfigFile " + configPath[i] + " found and loaded." );
            break;
        } else {
            LOG4CXX_DEBUG ( logger42, "ConfigFile " + configPath[i] + " not found." );
        }
    }
}