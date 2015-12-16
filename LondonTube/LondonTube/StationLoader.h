#ifndef STATION_LOADER_H_INCLUDED
#define STATION_LOADER_H_INCLUDED

#include <string>
#include <vector>

#include "Station.h"
#include "Log.h"
#include "Util.h"

namespace StationLoader{

	inline void load(const std::string & filename, std::vector<Station> & stations){

		std::ifstream infile;
		infile.open(filename.c_str());  

		if(!infile) {
			Log::logInfo("error loading file: "+filename);
		}

		std::string str_line;
		while(getline(infile, str_line)) { 
			Log::logInfo("===================Loading Station=====================");
			Log::logInfo(str_line);

			std::vector<std::string> tokens;
			boost::split(tokens, str_line, boost::is_any_of("|"));   

			if(tokens.size() != 4){
				Log::logInfo("Wrong format: "+ str_line);
				break;
			}

			//0: id  1: name 2: neighbor ids 3: line ids
			int id(Util::strToInt(tokens[0]));
			std::string name(tokens[1]);

			std::vector<int> neighbour_ids;
			std::vector<int> line_ids;
			std::vector<std::string> str_neighbour_ids;
			std::vector<std::string> str_line_ids;

			boost::split(str_neighbour_ids, tokens[2], boost::is_any_of(","));   
			boost::split(str_line_ids, tokens[3], boost::is_any_of(",")); 

			BOOST_FOREACH(const std::string & neighbour_id, str_neighbour_ids){
				neighbour_ids.push_back(Util::strToInt(neighbour_id));
			}

			BOOST_FOREACH(const std::string & line_id, str_line_ids){
				line_ids.push_back(Util::strToInt(line_id));
			}

			Station s(id,name,neighbour_ids,line_ids);
			s.printAll();

			stations.push_back(s);
		}
	}

}

#endif /* STATION_LOADER_H_INCLUDED */