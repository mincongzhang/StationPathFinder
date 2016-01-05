#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include <vector>         // std::vector
#include <functional>     // std::greater
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <utility>		  // std::pair
#include <algorithm>      // std::reverse
#include <boost/foreach.hpp>

#include "Util.h"

//Reference:
//http://www.cplusplus.com/reference/queue/priority_queue/priority_queue/
//http://www.redblobgames.com/pathfinding/a-star/introduction.html

namespace{
	class DNode{
	private:
		int m_value;
		double m_priority;

	public:
		DNode(const int value,const double priority=0.0): m_value(value), m_priority(priority){};
		~DNode(){};

		void setPriority(const double priority){ m_priority = priority; };
		double  getPriority() const { return m_priority; };
		int getValue() const { return m_value; };
	};

	class compareDNode{
	private:
		bool m_reverse;
	public:
		compareDNode(bool reverse=false):m_reverse(reverse){};
		bool operator()(const DNode & n1, const DNode & n2){
			if(m_reverse) return (n1.getPriority() < n2.getPriority());
			return (n1.getPriority() > n2.getPriority());
		}
	};
}

class Dijkstra{
private:
	typedef double Cost;
	boost::unordered_map<int,Cost> m_cost;
	boost::unordered_map<int,Station> m_stations;
	const boost::unordered_map<int,Station> m_const_stations; //TODO: cost memory, might need a dictionary?
	boost::unordered_map<int,int> m_came_from;
	std::priority_queue<DNode, std::vector<DNode>, compareDNode >  m_frontier;

	int m_start_id;
	int m_end_id;

public:
	Dijkstra(const boost::unordered_map<int,Station> & stations): m_stations(stations),m_const_stations(stations){};
	Cost getCostBetweenStations(const int & cur_id, const int & next_id){

		//Check previous id (came from)
		boost::unordered_map<int,int>::const_iterator came_from_it = m_came_from.find(cur_id);
		if(came_from_it == m_came_from.end()) {
			logInfo("Error! Cannot find previous id for ["<<cur_id<<"]"); 
			return 0.0;
		}

		int pre_id = came_from_it->second;
		if(pre_id == -1){return 0.0;} //start id, came from nowhere (-1)

		boost::unordered_map<int,Station>::const_iterator pre_it, next_it;
		pre_it  = m_const_stations.find(pre_id);
		next_it = m_const_stations.find(next_id);
		if(pre_it == m_const_stations.end() || next_it == m_const_stations.end()){
			logInfo("Error! Cannot find id :["<<pre_id<<"] or ["<<next_id<<"]");
		}


		const boost::unordered_set<int> & pre_station_line_ids  = pre_it->second.getLineIds();
		const boost::unordered_set<int> & next_station_line_ids = next_it->second.getLineIds();
		BOOST_FOREACH(const int & line_id, pre_station_line_ids){
			if(next_station_line_ids.find(line_id) != next_station_line_ids.end()){
				return 1.0; //has same line
			}
		}

		//have to transfer between lines
		return 2.0;
	};

	std::vector<int> getPath(const int start_id, const int end_id){
		//Initialization
		DNode start_node(start_id);
		m_frontier.push(start_node);
		m_cost.insert( std::pair<int,Cost>(start_id,0.0) );   //0.0 priority = at the top of the priority_queue 
		m_came_from.insert( std::pair<int,int>(start_id,-1) ); //-1 means come from nowhere

		while (!m_frontier.empty()){
			DNode cur_node = m_frontier.top();
			m_frontier.pop();
			int cur_id = cur_node.getValue();

			//Reach end
			if(cur_id == end_id){ break; }

			//Get Current Station Info
			boost::unordered_map<int,Station>::const_iterator it_cur;
			it_cur = m_stations.find(cur_id);
			if(it_cur == m_stations.end()){
				logInfo("["<<cur_id<<" ] not found in stations");
				continue;
			}

			//Get Neighbors
			const boost::unordered_set<int> & neighbour_ids = it_cur->second.getNeighbourIds();
			BOOST_FOREACH(const int & neighbour_id, neighbour_ids){
				boost::unordered_map<int,Station>::const_iterator it_neighbour;
				it_neighbour = m_stations.find(neighbour_id);
				if(it_neighbour == m_stations.end()){continue;}

				//Get (1)current cost (2) cost between stations
				Cost unary_cost    = m_cost[cur_id];
				Cost pairwise_cost = getCostBetweenStations(cur_id,neighbour_id);
				Cost new_cost = unary_cost + pairwise_cost;
				//logInfo("TESTING: Checking cost: " <<cur_id<<" to "<<neighbour_id<<" Cost: " <<pairwise_cost);

				//Decide if move forward 
				boost::unordered_map<int,Cost>::const_iterator cost_it;
				cost_it = m_cost.find(neighbour_id);
				if(cost_it == m_cost.end() || new_cost < cost_it->second){
					m_cost[neighbour_id] = new_cost; // not efficient, but clear
					m_frontier.push(DNode(neighbour_id,new_cost));
					m_came_from.insert( std::pair<int,int>(neighbour_id,cur_id) );
				}
			}
			m_stations.erase(it_cur);
		}// end of while (!m_frontier.empty())

		//Get path
		std::vector<int> path;
		extractPath(end_id,path);
		return path;
	}; //end of getPath()

	void extractPath(const int & end_id, std::vector<int> & path){
		int id = end_id;
		boost::unordered_map<int,int>::const_iterator path_it;
		while(true){
			path.push_back(id);
			path_it = m_came_from.find(id);
			if(path_it == m_came_from.end()){
				logInfo("Error! Unknown station id in m_came_from:["<<id<<"]");
				break;
			}

			id = path_it->second;
			if(id == -1) break;
		}
		std::reverse(path.begin(),path.end());
	}

};// end of class Dijkstra

#endif /* DIJKSTRA_H_INCLUDED */