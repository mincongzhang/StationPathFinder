#ifndef STATION_H_INCLUDED
#define STATION_H_INCLUDED

#include <string>
#include <vector>
#include <boost/foreach.hpp>

#include "Log.h"
#include "Util.h"

class Station{
private:
	int m_id;
	std::string m_name;
	std::vector<int> m_neighbour_ids;
	std::vector<int> m_line_ids;

public:
	Station(const int id, const std::string & name,
			const std::vector<int> & neighbour_ids, const std::vector<int> & line_ids):
	m_id(id),m_name(name),m_neighbour_ids(neighbour_ids),m_line_ids(line_ids){}


	void printId(){
		Log::logInfo( "Station Id : [" + Util::toString(m_id) + "]" );
	}
	void printName(){
		Log::logInfo( "Station name :[" + m_name +"]");
	}

	void printNeighbourIds(){
		std::string neighbours;
		BOOST_FOREACH(const int & neighbour_id, m_neighbour_ids){
			neighbours += Util::toString(neighbour_id) + "," ;
		}
		neighbours.pop_back();

		Log::logInfo( "Neighbour Ids :[" + neighbours +"]");
	}

	void printLineIds(){
		std::string lines;
		BOOST_FOREACH(const int & line_id, m_line_ids){
			lines += Util::toString(line_id) + "," ;
		}

		lines.pop_back();

		Log::logInfo( "Line Ids :[" + lines +"]");
	}

	void printAll(){
		printId();
		printName();
		printNeighbourIds();
		printLineIds();
	}

};


#endif /* STATION_H_INCLUDED */