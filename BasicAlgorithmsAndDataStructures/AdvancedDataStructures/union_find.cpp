#include <union_find.h>

Node::Node(const int & x) {
	el = x;
	parent = this;
	rank = 0;
}

Node* Node::findSet() {
	Node * x = this;
	while (x->parent != x)
		x = x->parent;
	return x;
}

const Node* Node::findSet() const {
	const Node * x = this;
	while (x->parent != x)
		x = x->parent;
	return x;
}

Node* Node::link(Node * y) {
	Node * x = this;
	if (x->getRank() > y->getRank()) {
		y->parent = x;
		return x;
	}
	else {
		x->parent = y;
		if (x->getRank() == y->getRank())
			x->setRank(x->getRank() + 1);
		return x;
	}
}

int Node::getEl() const
{
	return el;
}

int Node::getRank() const
{
	return rank;
}

void Node::setRank(const int & r)
{
	rank = r;
}

Node* Node::unionSet(Node * y) {
	return this->findSet()->link(y->findSet());
}