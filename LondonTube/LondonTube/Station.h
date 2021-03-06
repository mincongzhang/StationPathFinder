#ifndef STATION_H_INCLUDED
#define STATION_H_INCLUDED

#include <string>
#include <vector>
#include <boost/unordered_set.hpp>
#include <boost/foreach.hpp>

#include "Log.h"
#include "Util.h"

class Station{
private:
	int m_id;
	std::string m_name;
	boost::unordered_set<int> m_neighbour_ids;
	boost::unordered_set<int> m_line_ids;

public:
	Station(const int id, const std::string & name,
			const boost::unordered_set<int> & neighbour_ids, const boost::unordered_set<int> & line_ids):
	m_id(id),m_name(name),m_neighbour_ids(neighbour_ids),m_line_ids(line_ids){}

	const boost::unordered_set<int> & getNeighbourIds() const {return m_neighbour_ids;};
	const boost::unordered_set<int> & getLineIds() const {return m_line_ids;};

	void printId() const{
		logInfo( "Station Id : ["<<m_id<<"]" );
	}
	void printName() const {
		logInfo( "Station name :[" + m_name +"]");
	}

	void printNeighbourIds() const{
		std::string neighbours;
		BOOST_FOREACH(const int & neighbour_id, m_neighbour_ids){
			neighbours += Util::toString(neighbour_id) + "," ;
		}
		neighbours.pop_back();

		logInfo( "Neighbour Ids :["<<neighbours<<"]");
	}

	void printLineIds() const{
		std::string lines;
		BOOST_FOREACH(const int & line_id, m_line_ids){
			lines += Util::toString(line_id) + "," ;
		}

		lines.pop_back();

		logInfo( "Line Ids :[" + lines +"]");
	}

	void printAll() const{
		printId();
		printName();
		printNeighbourIds();
		printLineIds();
	}

};


#endif /* STATION_H_INCLUDED */