#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater

	class DNode{
	private:
		int m_value;
		int m_priority;

	public:
		DNode(const int value): m_value(value){};
		~DNode(){};

		void setPriority(const int priority){ m_priority = priority; };
		int  getPriority() const { return m_priority; };
		bool operator > (DNode & n){ return this->getPriority() > n.getPriority(); };
		bool operator < (DNode & n){ return this->getPriority() < n.getPriority(); };
	};



#endif /* DIJKSTRA_H_INCLUDED */