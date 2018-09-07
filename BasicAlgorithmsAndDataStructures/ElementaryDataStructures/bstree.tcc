template<typename K>
void inorderVisit(const TreeNode<K> * root, const TreeNode<K> * sentinel, const int & n) {
	const TreeNode<K>** stack = new const TreeNode<K>*[n];
	const TreeNode<K> * curr = root;
	int s = 0;
	while (curr != sentinel || s > 0) {
		while (curr != sentinel) {
			stack[s++] = curr;
			curr = curr->left;
		}
		curr = stack[--s];
		std::cout << curr->key << " ";
		curr = curr->right;
	}
	std::cout << std::endl;

	delete[] stack;
}

template<typename K>
void depthGiveNode(const TreeNode<K> * root, const TreeNode<K> * sentinel, const int & n) {
	const TreeNode<K>** stack = new const TreeNode<K>*[n];
	int *stack_depth = new int[n];

	stack[0] = root;
	stack_depth[0] = 0;
	int s = 1;
	int init = 0, end = 1, curr_depth, max_depth = 0;
	const TreeNode * curr;
	while (s > 0) {
		curr_depth = stack_depth[init];
		max_depth = (curr_depth > max_depth) ? curr_depth : max_depth;
		curr = stack[init++];
		--s;
		if (curr->left != sentinel) {
			stack_depth[end] = curr_depth + 1;
			stack[end++] = curr->left;
			++s;
		}
		if (curr->right != sentinel) {
			stack_depth[end] = curr_depth + 1;
			stack[end++] = curr->right;
			++s;
		}
	}
	std::cout << "Depth : " << max_depth;
}

template<typename K>
TreeNode<K> * BinarySearchTree<K>::maximum(TreeNode<K> * x) {
	while (x->right != nil)
		x = x->right;
	return x;
}

template<typename K>
TreeNode<K> * BinarySearchTree<K>::minimum(TreeNode<K> * x) {
	while (x->left != nil)
		x = x->left;
	return x;
}

template<typename K>
void BinarySearchTree<K>::transplant(TreeNode * x, TreeNode *y) {
	if (x->parent == root)
		root = y;
	if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->parent = x->parent;
}

template<typename K>
BinarySearchTree<K>::BinarySearchTree() {
	nil = new TreeNode<K>();
	nil->left = nil->right = nil->parent = nil;
	root = nil;
	size = 0;
}

template<typename K>
BinarySearchTree<K>::~BinarySearchTree() {
	delete nil;
}

template<typename K>
void BinarySearchTree<K>::insert(TreeNode<K> * x) {
	if (root == nil) {
		root = x;
		x->parent = nil;
	}
	else {
		TreeNode<K> *y = nil, *z = root;
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
	}
	x->left = x->right = nil;
	++size;
}

template<typename K>
void BinarySearchTree<K>::remove(TreeNode<K> * x) {
	if (x->left == nil)
		transplant(x, x->right);
	else if (x->right == nil)
		transplant(x, x->right);
	else {
		TreeNode<K> * y = minimum(x->right);
		if (y->parent != x) {
			transplant(y, y->right);
			y->right = x->right;
			y->right->parent = y;
		}
		transplant(x, y);
		y->left = x->left;
		y->left->parent = y;
	}
	--size;
}

template<typename K>
TreeNode<K> * BinarySearchTree<K>::search(const int & k) {
	TreeNode<K> * x = root;
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
int BinarySearchTree<K>::getSize() const {
	return size;
}

template<typename K>
const TreeNode<K> * BinarySearchTree<K>::getRoot() const {
	return root;
}

template<typename K>
const TreeNode<K> * BinarySearchTree<K>::getSentinel() const {
	return nil;
}