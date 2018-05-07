#pragma once
#ifndef __GRAPH_H
#define __GRAPH_H
#include <list.h>

class Node {
public:
	Node();
	void addAdjacent(Node * u);
	int degree() const;
private:
	List<Node*> adjacent;
	int color;
};

class Graph {
public:
	Graph();
	void insertNode(Node * v);
	bool insertArc(Node * u, Node *v);
private:
	List<Node*> nodes;
};

#endif