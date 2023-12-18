#ifndef HashNode_h
#define HashNode_h

#include <iostream>	
#include "AVLTree.h"

template <class T> class HashNode;

template <> class HashNode<int> /*: protected AVLTree<int>*/
{
private:
	int key;
	AVLTree<int>* collisionList;

public:
	HashNode() : key(int()), collisionList(new AVLTree<int>()) {}
	HashNode(const int& inpKey) : key(inpKey), collisionList(new AVLTree<int>()) {}
	~HashNode() {
		if (collisionList != nullptr) {
			(*collisionList).clear_tree();
			delete collisionList;
			collisionList = nullptr;
		}
	}

	bool has_collision() const {
		return (*collisionList).is_empty() == false;
	}

	void insert(const int& inpKey) {
		(*collisionList).insert(inpKey);
	}

	bool search(const int& inpKey) const {
		if (key == inpKey) return true;
		else {
			return (*collisionList).search(inpKey);
		}
	}

	void display() const {
		std::cout << std::setw(3) << std::setfill('0') << key << " ";
		std::cout << *collisionList;
	}

	int count_conllisions() const {
		return (*collisionList).count();
	}

	friend std::ostream& operator<<(std::ostream& os, const HashNode<int>& inpNode) {
		
	}
};

template <class T> class HashMap;


#endif // !HashNode_h