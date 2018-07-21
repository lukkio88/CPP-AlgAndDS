#include <list.h>

List::List() {
	nil = new Node();
	nil->next = nil->prev = nil;
	size = 0;
};
List::~List() { 
	; 
}

void List::insert(Node * x) {
	x->prev = nil;
	x->next = nil->next;
	nil->next->prev = x;
	nil->next = x;
	++size;
}

void List::remove(Node * x) {
	x->prev->next = x->next;
	x->next->prev = x->prev;
	--size;
}

Node * List::search(const int & k) {
	Node * x = nil->next;
	while (x != nil && x->key != k)
		x = x->next;
	if (x == nil)
		return nullptr;
	return x;
}

int List::getSize() const {
	return size;
}