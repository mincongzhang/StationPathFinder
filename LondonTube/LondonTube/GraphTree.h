#ifndef GRAPH_TREE_H_INCLUDED
#define GRAPH_TREE_H_INCLUDED

#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>

#include "Station.h"
#include "Log.h"

namespace{

	class Node;
	typedef Node* NodePtr;
	typedef boost::unordered_map<int,NodePtr> NodeMap;
	typedef NodeMap::value_type NodePair;

	class Node{
	private:
		NodePtr m_parent;
		NodeMap m_children;
		int     m_value;

	public:
		~Node(){};
		Node(int value, NodePtr parent): m_value(value), m_parent(parent) {};

		void appendChild(int id){
			NodePtr node_ptr = new Node(id,this/*parent node*/);
			m_children.insert(NodePair(id,node_ptr));
		};

		const NodeMap & getChildren(){
			return m_children;
		};

		NodePtr getParent(){
			return m_parent;
		};

		int getId(){ return m_value;};
	};

}

class GraphTree{
private:
	boost::unordered_map<int,Station> m_stations;
	NodePtr m_root;
	NodePtr m_target_node;
	std::vector< std::vector<int> > m_shortest_paths;
	int m_start_id;
	int m_end_id;

public:
	GraphTree(const boost::unordered_map<int,Station> & stations): m_stations(stations){};

	void buildTree(){
		m_root = new Node(m_start_id,NULL);
		std::queue<NodePtr> node_queue;
		node_queue.push(m_root);
		buildTree(node_queue);
	};

	void buildTree(std::queue<NodePtr> & node_queue){
		while(!node_queue.empty()){
			NodePtr p_node = node_queue.front();
			node_queue.pop();

			int id = p_node->getId();
			boost::unordered_map<int,Station>::iterator it = m_stations.find(id);
			if(it == m_stations.end()) continue;
			//logInfo("Searching:"<<id);

			//get neighbors
			const boost::unordered_set<int> & neighbour_ids = it->second.getNeighbourIds();
			BOOST_FOREACH(const int & neighbour_id, neighbour_ids){
				if(m_stations.find(neighbour_id) != m_stations.end())
					p_node->appendChild(neighbour_id);
			}

			//get children
			const NodeMap & children = p_node->getChildren();

			//iterate children and push to queue
			BOOST_FOREACH(NodePair pair, children){
				if(pair.first == m_end_id){
					//logInfo("TESTING: Got target! :"<<m_end_id);

					//trace back and get path
					std::vector<int> path;
					NodePtr tmp_node = pair.second;
					while(tmp_node != NULL){
						int tmp_id = tmp_node->getId();
						path.push_back(tmp_id);
						//logInfo("TESTING: path: "<<tmp_id);
						tmp_node = tmp_node->getParent();
					}

					std::reverse(path.begin(),path.end());
					m_shortest_paths.push_back(path);
				}
				node_queue.push(pair.second);
			}

			//get rid of itself
			m_stations.erase(it);
		};
	};

	const std::vector< std::vector<int> > & getPath(const int start_id, const int end_id){
		m_start_id = start_id;
		m_end_id = end_id;

		logInfo("Searching for shortest path with start and end stations:");
		boost::unordered_map<int,Station>::const_iterator it;
		it = m_stations.find(m_start_id);
		if(it == m_stations.end()){logInfo("ERROR! Unknown id in the path"); }
		it->second.printName();

		it = m_stations.find(m_end_id);
		if(it == m_stations.end()){logInfo("ERROR! Unknown id in the path"); }
		it->second.printName();


		buildTree();
		return m_shortest_paths;		
	};
};

#endif /* GRAPH_TREE_H_INCLUDED */