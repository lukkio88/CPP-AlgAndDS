#pragma once
#ifndef __GRAPH_H
#define __GRAPH_H
#include <list.h>

struct Node {
	int key;
	int color;
	List<Node*> adjacent;
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