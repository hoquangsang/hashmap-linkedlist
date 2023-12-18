#ifndef TreeNode_h
#define TreeNode_h
#include <iostream>
#include <iomanip>

enum heightstt {
	h_leaf = 1,
	h_null = 0,
};

enum keyvaluestt {
	MIN_KEY = INT_MIN,
	MAX_KEY = INT_MAX,
};

template <class T> class Node;

template <> class Node<int> 
{
private:
	int key;
	Node<int>* left;
	Node<int>* right;
	int height;
public:
	Node();
	Node(const int& inpKey);
	Node(const int& inpKey, Node<int>* leftPtr, Node<int>* rightPtr);
	Node(const Node<int>& inpNode);
	
	// getter methods
	int get_key() const;
	int get_height() const;
	int get_balance() const;
	Node<int>*& get_leftptr();
	Node<int>*& get_rightptr();

	// setter methods
	void set_key(const int& inpKey);
	void set_leftptr(Node<int>* nodePtr);
	void set_rightptr(Node<int>* nodePtr);

	// update
	virtual void update_height();

	// ostream opearator
	friend std::ostream& operator<<(std::ostream& os, const Node<int>& inpNode) {
		os << "->" << std::setw(3) << std::setfill('0') << inpNode.get_key();
		return os;
	}
private:
	virtual int get_height(Node<int>* nodePtr) const;

protected:
};

#pragma region Tree Node Methods

// constructor & parameterize
Node<int>::Node() : key(int()), left(nullptr), right(nullptr), height(h_null) {}
Node<int>::Node(const int& inpKey) : key(inpKey), left(nullptr), right(nullptr), height(h_leaf) {}
Node<int>::Node(const int& inpKey, Node<int>* leftPtr, Node<int>* rightPtr) : key(inpKey), height(h_leaf) {
	left = leftPtr;
	right = rightPtr;
	height = 1 + std::max(get_height(left), get_height(right));
}
Node<int>::Node(const Node<int>& inpNode) : key(inpNode.key), left(nullptr), right(nullptr), height(inpNode.height) {
	if (inpNode.left != nullptr) {
		left = new Node<int>(*inpNode.left);
	}
	if (inpNode.right != nullptr) {
		right = new Node<int>(*inpNode.right);
	}
}

// getter methods
int Node<int>::get_key() const {
	return key;
}
int Node<int>::get_height() const {
	return height;
}
int Node<int>::get_balance() const {
	int left_height = (left == nullptr) ? 0 : left->height;
	int right_height = (right == nullptr) ? 0 : right->height;
	return right_height - left_height;
}

Node<int>*& Node<int>::get_leftptr() {
	return left;
}
Node<int>*& Node<int>::get_rightptr() {
	return right;
}

// setter methods
void Node<int>::set_key(const int& inpKey) {
	key = inpKey;
}
void Node<int>::set_leftptr(Node<int>* nodePtr) {
	left = nodePtr;
}
void Node<int>::set_rightptr(Node<int>* nodePtr) {
	right = nodePtr;
}

// update
void Node<int>::update_height() {
	height = 1 + std::max(get_height(left), get_height(right));
}

// private:
int Node<int>::get_height(Node<int>* nodePtr) const {
	if (nodePtr == nullptr) return h_null;
	return nodePtr->get_height();
}

// protected
#pragma endregion

#endif //!TreeNode_h