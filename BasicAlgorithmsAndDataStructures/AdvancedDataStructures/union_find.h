#pragma once
#ifndef __UNION_FIND
#define __UNION_FIND

class Node {
public:
	Node(const int & el);
	const Node* findSet() const;
	Node* findSet();
	Node* unionSet(Node * x);
	Node* link(Node * x);
	int getEl() const;
	int getRank() const;
	void setRank(const int & r);
private:
	int el;
	int rank;
	Node* parent;
};

#endif