#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include <vector>         // std::vector
#include <functional>     // std::greater
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <utility>		  // std::pair
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
	std::priority_queue<DNode, std::vector<DNode>, compareDNode >  m_frontier;

	int m_start_id;
	int m_end_id;

public:
	Dijkstra(const boost::unordered_map<int,Station> & stations): m_stations(stations){};
	Cost getCostBetweenStations(boost::unordered_map<int,Station>::const_iterator & it1, boost::unordered_map<int,Station>::const_iterator & it2){
		const boost::unordered_set<int> & line_ids1 = it1->second.getLineIds();
		const boost::unordered_set<int> & line_ids2 = it2->second.getLineIds();
		BOOST_FOREACH(const int & line_id, line_ids1){
			if(line_ids2.find(line_id) != line_ids2.end()){
				return 1.0; //has same line
			}
		}

		//have to transfer between lines
		return 1.5;
	};

	void getPath(const int start_id, const int end_id){
		//initialization: start node with cost 0.0
		DNode start_node(start_id);
		m_frontier.push(start_node);
		m_cost.insert( std::pair<int,Cost>(start_id,0.0) );

		while (!m_frontier.empty()){
			DNode cur_node = m_frontier.top();
			m_frontier.pop();

			if(cur_node.getValue() == end_id){
				Log::logInfo("Reach end id");
				Log::logInfo(cur_node.getValue());
				break;
			}
			Log::logInfo("Next station: [" + Util::toString(cur_node.getValue() ) + "]");

			boost::unordered_map<int,Station>::const_iterator it_cur;
			it_cur = m_stations.find(cur_node.getValue());
			if(it_cur == m_stations.end()){
				Log::logInfo("[" + Util::toString(cur_node.getValue()) + " ] not found in stations");
				continue;
			}

			//get neighbors
			const boost::unordered_set<int> & neighbour_ids = it_cur->second.getNeighbourIds();
			BOOST_FOREACH(const int & neighbour_id, neighbour_ids){
				boost::unordered_map<int,Station>::const_iterator it_neighbour;
				it_neighbour = m_stations.find(neighbour_id);
				if(it_neighbour == m_stations.end()){continue;}

				//get current cost, plus cost between stations
				Cost unary_cost    = m_cost[cur_node.getValue()];
				Cost pairwise_cost = getCostBetweenStations(it_cur,it_neighbour);
				Cost new_cost = unary_cost + pairwise_cost;

				//decide if add to frontier or not
				boost::unordered_map<int,Cost>::const_iterator cost_it;
				cost_it = m_cost.find(neighbour_id);
				if(cost_it == m_cost.end() || new_cost < cost_it->second){
					m_cost.insert(std::pair<int,Cost>(neighbour_id,new_cost));
					m_frontier.push(DNode(neighbour_id,new_cost));
				}
			}
			m_stations.erase(it_cur);
		}
	};
};

#endif /* DIJKSTRA_H_INCLUDED */