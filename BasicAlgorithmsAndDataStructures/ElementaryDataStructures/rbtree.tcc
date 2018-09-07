template<typename K>
RBTree<K>::RBTree()
{
	nil = new RBTreeNode<K>();
	nil->left = nil->right = nil->parent = nil;
	root = nil;
	nil->color = BLACK;
}

template<typename K>
RBTree<K>::~RBTree()
{
	delete nil;
}

template<typename K>
void RBTree<K>::insert(RBTreeNode<K> * x)
{
	if (root == nil) {
		root = x;
		x->parent = nil;
		x->color = BLACK;
		x->left = x->right = nil;
	}
	else {
		RBTreeNode<K> *y = nil, *z = root;
		while (z != nil) {
			y = z;
			if (x->key < z->key)
				z = z->left;
			else
				z = z->right;
		}
		if (x->key < y->key)
			y->left = x;
		else
			y->right = x;
		x->parent = y;
		x->color = RED;
		x->left = x->right = nil;
		if (y->color == RED) insertFixup(x);
	}
}

template<typename K>
void RBTree<K>::remove(RBTreeNode<K> * x)
{
	RBTreeNode<K> * y = x, *z;
	int y_original_color = y->color;
	if (x->left == nil) {
		z = x->right;
		transplant(x, z);
	}
	else if (x->right == nil) {
		z = x->left;
		transplant(x, z);
	}
	else {
		y = minimum(x->right);
		z = y->right;
		y_original_color = y->color;
		if (y->parent != x) {
			transplant(y, z);
			y->right = x->right;
			y->right->parent = y;
		}
		transplant(x, y);
		y->left = x->left;
		y->left->parent = x->parent;
		y->color = x->color;
	}
	if (y_original_color == BLACK)
		removeFixup(z);
}

template<typename K>
RBTreeNode<K> * RBTree<K>::search(const int & k)
{
	RBTreeNode<K> * x = root;
	while (x != nil) {
		if (k < x->key)
			x = x->left;
		else if (k > x->key)
			x = x->right;
		else
			return x;
	}
	return nullptr;
}

template<typename K>
RBTreeNode<K> * RBTree<K>::minimum(RBTreeNode<K> * x)
{
	while (x->left != nil)
		x = x->left;
	return x;
}

template<typename K>
RBTreeNode<K> * RBTree<K>::maximum(RBTreeNode<K> * x)
{
	while (x->right != nil)
		x = x->right;
	return x;
}

template<typename K>
void RBTree<K>::transplant(RBTreeNode<K> * x, RBTreeNode<K> * y)
{
	if (x == root)
		root = y;
	if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->parent = x->parent;
}

template<typename K>
RBTreeNode<K> * RBTree<K>::leftRotate(RBTreeNode<K> * x)
{
	RBTreeNode<K> * y = x->right;
	transplant(x, y);
	y->left->parent = x;
	x->right = y->left;
	y->left = x;
	return y;
}

template<typename K>
RBTreeNode<K> * RBTree<K>::rightRotate(RBTreeNode<K> * x)
{
	RBTreeNode<K> * y = x->left;
	transplant(x, y);
	y->right->parent = x;
	x->left = y->right;
	y->right = x;
	return y;
}

template<typename K>
void RBTree<K>::insertFixup(RBTreeNode<K> * x)
{
	while (x->parent->color == RED) {
		if (x->parent == x->parent->parent->left) {
			if (x->parent->parent->right->color == RED) {
				x->parent->color = BLACK;
				x->parent->parent->right->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->right) {
					x = x->parent;
					leftRotate(x);
				}
			}
			x->parent->color = BLACK;
			x->parent->parent->color = RED;
			rightRotate(x->parent->parent);
			x = x->parent;
		}
		else {
			if (x->parent->parent->left->color == RED) {
				x->parent->color = BLACK;
				x->parent->parent->left->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->left) {
					x = x->parent;
					rightRotate(x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				leftRotate(x->parent->parent);
				x = x->parent;
			}
		}
	}
}

template<typename K>
void RBTree<K>::removeFixup(RBTreeNode<K> * x)
{
	while (x != root || x->color == BLACK) {
		RBTreeNode * w;
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == RED) {
				x->parent->color = RED;
				w->color = BLACK;
				leftRotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->left->color == RED && w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(w);
					w = x->parent->right;
				}
				else {
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			}
		}
		else {
			if (x == x->parent->right) {
				w = x->parent->left;
				if (w->color == RED) {
					x->parent->color = RED;
					w->color = BLACK;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->right->color == RED && w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						leftRotate(w);
						w = x->parent->left;
					}
					else {
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						rightRotate(x->parent);
						x = root;
					}
				}
			}
		}
	}
	x->color = BLACK;
}