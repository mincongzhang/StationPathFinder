#ifdef WIN32
#include <windows>
#endif

#include <iostream>
#include <fstream>  
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/foreach.hpp>
#include <boost/unordered_map.hpp>

#include "Station.h"
#include "StationLoader.h"
#include "Log.h"
#include "Util.h"

int main(){

	std::string filename = "stations.txt";
	boost::unordered_map<int,Station> stations;
	//std::vector<Station> stations;

	StationLoader::load(filename,stations);

	system("PAUSE");
	return 0;

}