#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include <vector>         // std::vector
#include <functional>     // std::greater
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue

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
	boost::unordered_map<int,Cost> m_current_cost;
	boost::unordered_map<int,Station> m_stations;

	int m_start_id;
	int m_end_id;

public:
	Dijkstra(const boost::unordered_map<int,Station> & stations): m_stations(stations){};

	void getPath(const int start_id, const int end_id){

	};
};

void dijkstraTest(){
	DNode a(1),b(2),c(3);
	a.setPriority(1);
	b.setPriority(2);
	c.setPriority(3);

	std::vector<DNode> vec;
	std::priority_queue<DNode, std::vector<DNode>, compareDNode >  pq;
	pq.push(a);
	pq.push(b);
	pq.push(c);
	pq.pop();

	Log::logInfo(pq.top().getPriority());
}
#endif /* DIJKSTRA_H_INCLUDED */