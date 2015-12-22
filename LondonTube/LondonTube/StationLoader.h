#ifndef STATION_LOADER_H_INCLUDED
#define STATION_LOADER_H_INCLUDED

#include <string>
#include <vector>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <utility> //pair

#include "Station.h"
#include "Log.h"
#include "Util.h"

namespace StationLoader{

	inline void load(const std::string & filename, boost::unordered_map<int,Station> & stations){

		std::ifstream infile;
		infile.open(filename.c_str());  

		if(!infile) {
			Log::logInfo("error loading file: "+filename);
		}

		std::string str_line;
		while(getline(infile, str_line)) {
			//Log::logInfo("===================Loading Station=====================");
			//Log::logInfo(str_line);

			std::vector<std::string> tokens;
			boost::split(tokens, str_line, boost::is_any_of("|"));   

			if(tokens.size() != 4){
				Log::logInfo("Wrong format: "+ str_line);
				return;
			}

			//0: id  1: name 2: neighbor ids 3: line ids
			int id(Util::strToInt(tokens[0]));
			std::string name(tokens[1]);

			boost::unordered_set<int> neighbour_ids;
			boost::unordered_set<int> line_ids;
			std::vector<std::string> str_neighbour_ids;
			std::vector<std::string> str_line_ids;

			boost::split(str_neighbour_ids, tokens[2], boost::is_any_of(","));   
			boost::split(str_line_ids, tokens[3], boost::is_any_of(",")); 

			BOOST_FOREACH(const std::string & neighbour_id, str_neighbour_ids){
				neighbour_ids.insert(Util::strToInt(neighbour_id));
			}

			BOOST_FOREACH(const std::string & line_id, str_line_ids){
				line_ids.insert(Util::strToInt(line_id));
			}

			Station s(id,name,neighbour_ids,line_ids);

			stations.insert(std::pair<int,Station>(id,s));
		}

		//typedef std::pair<int,Station> StationIndex;
		//BOOST_FOREACH(const StationIndex & p, stations){
		//	Log::logInfo("===================Printing Station=====================");
		//	(p.second).printAll();
		//}

		Log::logInfo("===================Loading Done: ["+ Util::toString(stations.size()) + "] stations loaded. =====================");
	}

}

#endif /* STATION_LOADER_H_INCLUDED */