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
#include "Dijkstra.h"

int main(){

	std::string filename = "stations.txt";
	boost::unordered_map<int,Station> stations;

	StationLoader::load(filename,stations);

	/**********************Approach 1*******************************/
	/*
	    Breadth First Search: 
	    Build a tree with root = start station
	    Level order traverse to get shortest path	
	    It will return all possible shortest path, without considering line transferring
	
	    e.g. Liverpool st: 0, king's cross: 60
		paths = tree_path_finder.getPath(0,60);
	*/

	logInfo("====================== Breadth First Search ======================");
	std::vector< std::vector<int> > paths;
	GraphTree tree_path_finder(stations);
	paths = tree_path_finder.getPath(0,60);

	BOOST_FOREACH(std::vector<int> & path, paths){
		logInfo("Shortest path: ");
		BOOST_FOREACH(int & id, path){
			boost::unordered_map<int,Station>::const_iterator it = stations.find(id);
			if(it == stations.end()){logInfo("ERROR! Unknown id in the path :["<<id<<"]");  continue;}

			it->second.printName();
			//it->second.printLineIds();
		}
	}
	/***************************************************************/




	/**********************Approach 2*******************************/
	/*
		Dijkstra's Algorithm
	*/
	logInfo("====================== Dijkstra's Algorithm ======================");
	Dijkstra dijk_path_finder(stations);
	std::vector<int> path = dijk_path_finder.getPath(0,60);

	logInfo("Shortest path: ");
	BOOST_FOREACH(int & id, path){
		boost::unordered_map<int,Station>::const_iterator it = stations.find(id);
		if(it == stations.end()){logInfo("ERROR! Unknown id in the path :["<<id<<"]"); continue;}

		it->second.printName();
	}
	/***************************************************************/

	system("PAUSE");
	return 0;

}