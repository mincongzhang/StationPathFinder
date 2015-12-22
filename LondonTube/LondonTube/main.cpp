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
#include "GraphTree.h"

int main(){

	std::string filename = "stations.txt";
	boost::unordered_map<int,Station> stations;

	StationLoader::load(filename,stations);

	////////Liverpool st: 0
	////////king's cross: 60
	std::vector< std::vector<int> > paths;
	GraphTree tree(stations);
	paths = tree.getPath(0,60);

	BOOST_FOREACH(std::vector<int> & path, paths){
		Log::logInfo("Shortest path: ");
		BOOST_FOREACH(int & id, path){
			boost::unordered_map<int,Station>::const_iterator it = stations.find(id);
			if(it == stations.end()){Log::logInfo("ERROR! Unknown id in the path"); continue;}

			it->second.printName();
			//it->second.printLineIds();
		}
	}

	system("PAUSE");
	return 0;

}