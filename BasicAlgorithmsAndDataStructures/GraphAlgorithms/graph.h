#ifndef __GRAPH_H
#define __GRAPH_H

#include <list.h>

template<typename T>
struct GraphNode {
	T val;
	List<T> neighbourList;
};

template<typename T>
class Graph {
public:
	Graph();
	void addVertex()
private:
	List<GraphNode<T>> vertices;
};

#endif