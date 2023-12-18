#ifndef AVLTree_h
#define AVLTree_h

#include <iostream>
#include <queue>
#include "TreeNode.h"

enum balancestt {
	left_heavy = -1,
	LEFT_SKEWED = -2,
	right_heavy = 1,
	RIGHT_SKEWED = 2,
	BALANCED = 0
};

template <class T> class AVLTree;

template <> class AVLTree<int> {
protected:
private:
	//propertie
	Node<int>* root;

	//maintain AVL properties
	void update_height(Node<int>*& inpRoot);
	void rotate_left(Node<int>*& inpRoot);
	void rotate_right(Node<int>*& inpRoot);
	void update_balance(Node<int>*& inpRoot);

public:
	AVLTree();
	AVLTree(const int& inpKey);
	AVLTree(const Node<int>& inpNode);
	AVLTree(const AVLTree<int>& inpTree);
	~AVLTree();
	
	// traversal
	void in_order_traversal() const;
	void pre_order_traversal() const;
	void post_order_traversal() const;
	void level_order_traversal() const;

	// boolean
	bool is_empty() const;
	bool is_AVL() const;
	bool search(const int& inpKey) const;

	// getter methods
	Node<int>*& get_root();
	int height_tree() const;
	int get_max() const;
	int get_min() const;
	int count() const;

	// inserter & remove
	void insert(const int& inpKey);
	void remove(const int& inpKey);
	
	// finder methods

	// clear
	void clear_tree();

	// ostream
	friend std::ostream& operator<<(std::ostream& os, const AVLTree<int>& inpTree) {
		inpTree.pre_order_traversal();
		return os;
	}

private: // for Node
	// traversal
	void in_order_traversal(Node<int>* inpRoot) const;
	void pre_order_traversal(Node<int>* inpRoot) const;
	void post_order_traversal(Node<int>* inpRoot) const;
	void level_order_traversal(Node<int>* inpRoot) const;

	// boolean
	bool is_AVL(Node<int>* inpRoot, int min = MIN_KEY, int max = MAX_KEY) const;
	bool search(Node<int>* inpRoot, const int& inpKey) const;

	// getter
	Node<int>* min_node(Node<int>* inpRoot) const;
	Node<int>* max_node(Node<int>* inpRoot) const;
	int count(Node<int>* inpRoot) const;
	int get_height(Node<int>* inpRoot) const;

	// insert & remove
	void insert(Node<int>*& inpRoot, const int& inpKey);
	void remove(Node<int>*& inpRoot, const int& inpKey);

	// clear
	Node<int>* copy_node(Node<int>* inpNode);
	void clear_tree(Node<int>*& inpRoot);
};

#pragma region maintain AVL
void AVLTree<int>::update_height(Node<int>*& inpRoot) {
	if (inpRoot == nullptr) return;
	inpRoot->update_height();
}
void AVLTree<int>::rotate_left(Node<int>*& inpRoot) {
	if (inpRoot == nullptr) return;
	Node<int>* tempPtr = inpRoot->get_rightptr();
	inpRoot->set_rightptr(tempPtr->get_leftptr());
	tempPtr->set_leftptr(inpRoot);

	update_height(inpRoot);
	update_height(tempPtr);

	inpRoot = tempPtr;
}
void AVLTree<int>::rotate_right(Node<int>*& inpRoot) {
	if (inpRoot == nullptr) return;
	Node<int>* tempPtr = inpRoot->get_leftptr();
	inpRoot->set_leftptr(tempPtr->get_rightptr());
	tempPtr->set_rightptr(inpRoot);

	update_height(inpRoot);
	update_height(tempPtr);

	inpRoot = tempPtr;
}
void AVLTree<int>::update_balance(Node<int>*& inpRoot) {
	if (inpRoot == nullptr) return;

	switch (inpRoot->get_balance())
	{
	case LEFT_SKEWED:
	{
		Node<int>*& leftSubTree = inpRoot->get_leftptr();
		// left - right
		if (leftSubTree->get_balance() == right_heavy) {
			rotate_left(leftSubTree);
		}
		// left - left
		rotate_right(inpRoot);
		break;
	}
	case RIGHT_SKEWED:
	{
		Node<int>*& rightSubTree = inpRoot->get_rightptr();
		// right - left
		if (rightSubTree->get_balance() == left_heavy) {
			rotate_right(rightSubTree);
		}
		// right - right
		rotate_left(inpRoot);
		break;
	}
	}

	inpRoot->update_height();
}
#pragma endregion

#pragma region constructor & destructor
AVLTree<int>::AVLTree() : root(nullptr) {}
AVLTree<int>::AVLTree(const int& inpKey) : root(nullptr) {
	root = new Node<int>(inpKey);
}
AVLTree<int>::AVLTree(const Node<int>& inpNode) : root(nullptr) {
	root = new Node<int>(inpNode);
}
AVLTree<int>::AVLTree(const AVLTree<int>& inpTree) : root(nullptr) {
	root = new Node<int>(*inpTree.root);
}
AVLTree<int>::~AVLTree() {
	clear_tree(root);
}
#pragma endregion

#pragma region public method
// traversal
void AVLTree<int>::in_order_traversal() const {
	in_order_traversal(root);
}
void AVLTree<int>::pre_order_traversal() const {
	pre_order_traversal(root);
}
void AVLTree<int>::post_order_traversal() const {
	post_order_traversal(root);
}
void AVLTree<int>::level_order_traversal() const {
	level_order_traversal(root);
}

// boolean
bool AVLTree<int>::is_empty() const {
	return root == nullptr;
}
bool AVLTree<int>::is_AVL() const {
	return is_AVL(root);
}
bool AVLTree<int>::search(const int& inpKey) const {
	return search(root, inpKey);
}

// getter methods
Node<int>*& AVLTree<int>::get_root()  {
	return root;
}
int AVLTree<int>::height_tree() const {
	return root->get_height();
}
int AVLTree<int>::get_max() const {
	if (is_empty()) return int();
	return max_node(root)->get_key();
}
int AVLTree<int>::get_min() const {
	if (is_empty()) return int();
	return min_node(root)->get_key();
}
int AVLTree<int>::count() const {
	return count(root);
}

// inserter & remove
void AVLTree<int>::insert(const int& inpKey) {
	insert(root, inpKey);
}
void AVLTree<int>::remove(const int& inpKey) {
	remove(root, inpKey);
}

// finder methods

//clear
void AVLTree<int>::clear_tree() {
	clear_tree(root);
}
#pragma endregion

#pragma region private helpper
// traversal
void AVLTree<int>::in_order_traversal(Node<int>* inpRoot) const {
	if (!inpRoot) return;
	in_order_traversal(inpRoot->get_leftptr());
	in_order_traversal(inpRoot->get_rightptr());
	std::cout << *inpRoot << " ";
}
void AVLTree<int>::pre_order_traversal(Node<int>* inpRoot) const {
	if (!inpRoot) return;
	
	std::cout << *inpRoot << " ";
	pre_order_traversal(inpRoot->get_leftptr());
	pre_order_traversal(inpRoot->get_rightptr());
}
void AVLTree<int>::post_order_traversal(Node<int>* inpRoot) const {
	if (!inpRoot) return;
	post_order_traversal(inpRoot->get_leftptr());
	post_order_traversal(inpRoot->get_rightptr());
	std::cout << *inpRoot << " ";
}
void AVLTree<int>::level_order_traversal(Node<int>* inpRoot) const {
	if (!inpRoot)return;
	std::queue<Node<int>*> queue;
	queue.push(inpRoot);
	while (!queue.empty()) {
		Node<int>* cur_node = queue.front();
		std::cout << *inpRoot << " ";
		queue.pop();
		if (cur_node->get_leftptr()) {
			queue.push(cur_node->get_leftptr());
		}
		if (cur_node->get_rightptr()) {
			queue.push(cur_node->get_rightptr());
		}
	}
}

// boolean
bool AVLTree<int>::is_AVL(Node<int>* inpRoot, int min, int max) const {
	if (inpRoot == nullptr) return true;

	int key = inpRoot->get_key();

	if (min >= key || key >= max) {
		return false;
	}

	if (std::abs(inpRoot->get_balance()) > 1) {
		return false;
	}

	return is_AVL(inpRoot->get_leftptr(), min, key)
		&& is_AVL(inpRoot->get_rightptr(), key, max);
}
bool AVLTree<int>::search(Node<int>* inpRoot, const int& inpKey) const {
	if (inpRoot == nullptr) return false;

	else if (inpKey < inpRoot->get_key()) {
		return search(inpRoot->get_leftptr(), inpKey);
	}
	else if (inpKey > inpRoot->get_key()) {
		return search(inpRoot->get_rightptr(), inpKey);
	}
	// else
	return true;
}

// getter
Node<int>* AVLTree<int>::min_node(Node<int>* inpRoot) const {
	Node<int>* minNode = inpRoot;
	while (minNode->get_leftptr()) {
		minNode = minNode->get_leftptr();
	}
	return minNode;
}
Node<int>* AVLTree<int>::max_node(Node<int>* inpRoot) const {
	Node<int>* maxNode = inpRoot;
	while (maxNode->get_rightptr()) {
		maxNode = maxNode->get_rightptr();
	}
	return maxNode;
}
int AVLTree<int>::count(Node<int>* inpRoot) const {
	if (inpRoot == nullptr) return 0;

	return 1 + count(inpRoot->get_leftptr()) + count(inpRoot->get_rightptr());
}
int AVLTree<int>::get_height(Node<int>* inpRoot) const {
	if (inpRoot == nullptr) return 0;
	return inpRoot->get_height();
}

// insert & remove
void AVLTree<int>::insert(Node<int>*& inpRoot, const int& inpKey) {
	if (inpRoot == nullptr) {
		inpRoot = new Node<int>(inpKey);
		return;
	}
	else if (inpKey < inpRoot->get_key()) {
		insert(inpRoot->get_leftptr(), inpKey);
	}
	else if (inpKey > inpRoot->get_key()) {
		insert(inpRoot->get_rightptr(), inpKey);
	}
	else return;

	inpRoot->update_height();

	update_balance(inpRoot);
}
void AVLTree<int>::remove(Node<int>*& inpRoot, const int& inpKey) {
	if (inpRoot == nullptr) {
		std::cerr << "[!] key " << inpKey << " not exist\n";
		return;
	}
	else if (inpKey < inpRoot->get_key()) {
		remove(inpRoot->get_leftptr(), inpKey);
	}
	else if (inpKey > inpRoot->get_key()) {
		remove(inpRoot->get_rightptr(), inpKey);
	}
	else {
		if (inpRoot->get_leftptr() == nullptr) {
			Node<int>* reNode = inpRoot;
			inpRoot->set_rightptr(inpRoot->get_rightptr());
			delete reNode;
			reNode = nullptr;
		}
		else if (inpRoot->get_rightptr() == nullptr) {
			Node<int>* reNode = inpRoot;
			inpRoot->set_leftptr(inpRoot->get_leftptr());
			delete reNode;
			reNode = nullptr;
		}
		else {

			Node<int>* reNode = min_node(inpRoot->get_rightptr());
			inpRoot->set_key(reNode->get_key());
			remove(inpRoot->get_rightptr(), reNode->get_key());
		}
	}

	update_balance(inpRoot);
}

// clear
Node<int>* AVLTree<int>::copy_node(Node<int>* inpNode) {
	if (inpNode != nullptr) {
		Node<int>* newRoot = new Node<int>(inpNode->get_key());

		Node<int>* leftPtr = copy_node(inpNode->get_leftptr());
		Node<int>* rightPtr = copy_node(inpNode->get_rightptr());

		newRoot->set_leftptr(leftPtr);
		newRoot->set_rightptr(rightPtr);

		return newRoot;
	}
	return nullptr;
}
void AVLTree<int>::clear_tree(Node<int>*& inpRoot) {
	if (inpRoot) {
		Node<int>* leftPtr = inpRoot->get_leftptr();
		Node<int>* rightPtr = inpRoot->get_rightptr();
		clear_tree(leftPtr);
		clear_tree(rightPtr);
		delete inpRoot;
		inpRoot = nullptr;
	}
}

#pragma endregion

#endif // !AVLTree_h