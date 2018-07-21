#ifndef __LIST_H
#define __LIST_H

struct Node {
	int key;
	Node *prev, *next;
};

class List {
public:
	List();
	~List();
	void insert(Node * x);
	void remove(Node * x);
	Node * search(const int & k);
	int getSize() const;
private:
	Node *nil;
	int size;
};

#endif