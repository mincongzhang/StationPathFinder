#ifndef GRAPH_TREE_H_INCLUDED
#define GRAPH_TREE_H_INCLUDED

#include <queue>
#include <vector>
#include <utility>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>

#include "Station.h"
#include "Log.h"

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
	//Node(): m_parent(NULL),m_value(-1) {};
	Node(int value, NodePtr parent): m_value(value), m_parent(m_parent) {};

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

class GraphTree{
private:
	boost::unordered_map<int,Station> m_stations;
	NodePtr m_root;
	NodePtr m_target_node;
	std::vector<int> m_shortest_path;
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

			const boost::unordered_set<int> & neighbour_ids = it->second.getNeighbourIds();
			BOOST_FOREACH(const int & neighbour_id, m_neighbour_ids){
				p_node->appendChild(neighbour_id);
			}

			//get children
			const NodeMap & children = p_node->getChildren();

			//iterate children and push to queue

			//get rid of itself
			m_stations.erase(it);
		};

		/*
		if(p_node == NULL) return;
		//if(id == end_id) get back to root

		boost::unordered_map<int,Station>::iterator it = m_stations.find(id);
		if(it == m_stations.end()) return;

		const boost::unordered_set<int> & neighbour_ids = it->second.getNeighbourIds();
		BOOST_FOREACH(const int & neighbour_id, m_neighbour_ids){
		p_node->appendChild(neighbour_id);
		}

		//get rid of itself
		m_stations.erase(it);

		//TODO: level order handle children
		*/
	};

	void getPath(const int start_id, const int end_id, std::vector<int> & path): m_start_id(start_id), m_end_id(end_id){
		buildTree();
	};
};

#endif /* GRAPH_TREE_H_INCLUDED */