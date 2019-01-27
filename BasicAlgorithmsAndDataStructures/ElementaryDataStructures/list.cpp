#include <list.h>

List::List() {
	nil = new Node();
	nil->next = nil->prev = nil;
};

List::~List() { 
	Node * x = nil->next;
	Node * y;
	while (x != nil) {
		y = x->next;
		remove(x);
		delete x;
		x = y;
	}
	delete nil;
}

void List::insert(Node * x) {
	x->prev = nil;
	x->next = nil->next;
	nil->next->prev = x;
	nil->next = x;
}

void List::remove(Node * x) {
	x->prev->next = x->next;
	x->next->prev = x->prev;
}

Node * List::search(const int & k) {
	Node * x = nil->next;
	while (x != nil && x->key != k)
		x = x->next;
	if (x == nil)
		return nullptr;
	return x;
}