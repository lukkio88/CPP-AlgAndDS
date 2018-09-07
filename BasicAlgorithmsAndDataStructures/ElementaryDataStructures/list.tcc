template<typename V>
List<V>::List() {
	nil = new Node<V>();
	nil->next = nil->prev = nil;
	size = 0;
}

template<typename V>
List<V>::~List<V>() { 
	delete nil;
}

template<typename V>
void List<V>::insert(Node<V> * x) {
	x->prev = nil;
	x->next = nil->next;
	nil->next->prev = x;
	nil->next = x;
	++size;
}

template<typename V>
void List<V>::remove(Node<V> * x) {
	x->prev->next = x->next;
	x->next->prev = x->prev;
	--size;
}

template<typename V>
Node<V> * List<V>::search(const V & v) {
	Node<V> * x = nil->next;
	while (x != nil && x->val != v)
		x = x->next;
	if (x == nil)
		return nullptr;
	return x;
}

template<typename V>
int List<V>::getSize() const {
	return size;
}