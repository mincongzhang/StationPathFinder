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

	StationLoader::load(filename,stations);

	//from root *level order*
	//get neighbor into a small hash table 
	//search for target node id
	//delete node
	//search for neighbor
	//recursive
	////////////////TEST///////////////
	////////Liverpool st: 0
	////////king's cross: 60

	system("PAUSE");
	return 0;

}