//#include "TreeNode.h"
//#include "AVLTree.h"
//#include "HashMap.h"
//#include "HashNode.h"
#include "Header.h"

using namespace std;


int main(int argc, char **argv) {
	

	if (argc != 2) {
		//std::cerr << "[!] \n";
		//exit(1);
	}
	HashMap<int> hm(10, "test.txt");

	for (int i = 1; i < 100; i++) {
		hm.insert(i);
	}

	hm.display();

	for (int i = 1; i < 100; i++) {
		hm.search(rand() % 200 + 1);
	}
	

	return 1;
	Node<int> t, * p = 0;
	AVLTree<int> tree;

	tree.insert(1);
	tree.insert(2); tree.pre_order_traversal();	cout << endl;
	tree.insert(3); tree.pre_order_traversal();	cout << endl;
	tree.insert(4); tree.pre_order_traversal();	cout << endl;
	tree.insert(5); tree.pre_order_traversal();	cout << endl;
	tree.insert(6); tree.pre_order_traversal();	cout << endl;
	tree.insert(7); tree.pre_order_traversal();	cout << endl;
	tree.insert(8); tree.pre_order_traversal();	cout << endl;
	tree.insert(9); tree.pre_order_traversal();	cout << endl;
	tree.insert(10); tree.pre_order_traversal(); cout << endl;
	tree.insert(11); tree.pre_order_traversal(); cout << endl;
	tree.insert(12); tree.pre_order_traversal(); cout << endl;
	//tree.pre_order_traversal();	cout << endl;

	cout << tree.is_AVL() << endl;
	cout << tree.search(1) << " " << tree.search(10) << endl;
}