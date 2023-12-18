#ifndef HashMap_h
#define HashMap_h

#include <iostream>
#include <fstream>
#include <string>
#include "HashNode.h"
#include "AVLTree.h"
#include "TreeNode.h"

#define A (std::sqrt(5.00) - 1.00) / 2.00 

template <class T> class HashMap;



template <> class HashMap<int> //: public HashNode<int> 
{
protected:
	typedef HashNode<int>* Entry;
private:
	Entry* table;
	int size;
	std::ofstream output;

public:
	HashMap(const int& m, const std::string& filename) : table(nullptr), size(m) {
		output.open(filename);
		if (!output.is_open()) {
			std::cerr << "[!] khong the mo file " << filename <<"\n";
			exit(-1);
		}
		if (m < 1) size = 1;
		table = new (std::nothrow) Entry;
		output << "[constructor] - khoi tao ";
		table = new (std::nothrow) Entry[size];
		if (!table) {
			output << "khong thanh cong\n";
			output << "+ cap phat khong thanh cong bang T\n";
			output << "+ m = " << m << "\n";
			output << "+ output file = " << filename << "\n";
			output.close();
			exit(-1);
		}
		else {
			for (int idx = 0; idx < size; idx++) {
				table[idx] = nullptr;
			}
			output << "thanh cong\n";
			output << "+ m = " << m << "\n";
			output << "+ output file = " << filename << "\n";
		}

	}

	~HashMap() {
		int count = 0;
		for (int idx = 0; idx < size; idx++) {
			if (table[idx] != nullptr) {
				count += table[idx]->count_conllisions();
				delete table[idx];
				table[idx] = nullptr;
			}
		}
		delete[] table;
		output << "[destructor] - huy bo thanh cong\n";
		output << "+ so phan tu xung dot da delete = " << count << "\n";
		output << "+ da delete bang T\n";
		output.close();
	}

	void insert(const int& key) {
		int hashValue = hash_function(key);

		if (table[hashValue] == nullptr) {
			table[hashValue] = new HashNode<int>(key);
		}
		else {
			table[hashValue]->insert(key);
		}

		output << "- thanh cong\n";

		output << "+ key = " << key << "\n";
		output << "+ hash value = " << hashValue << "\n";
		output << "+ xung dot: ";
		if (table[hashValue]->has_collision()) {
			output << "[co]\n";
		}
		else output << "[khong]\n";
	}

	void search(const int& key) {
		int hashValue = hash_function(key);

		bool found, collision;
		if (table[hashValue] == nullptr) {
			found = false;
			collision = false;
		}
		else {
			found = table[hashValue]->search(key);
			collision = table[hashValue]->has_collision();
		}

		if (found == true) output << "- tim thay\n";
		else output << "- khong tim thay\n";

		output << "+ key =	" << key << "\n";
		output << "+ hash value = " << hashValue << "\n";
		output << "+ xung dot: ";

		if (collision) {
			output << "[khong]\n";
		}
		else output << "[co]\n";
	}

	void insert_from_list(const int* list, const int& size) {
		for (int idx = 0; idx < size; idx++) {
			output << "[insert " << idx + 1 << "] ";
			insert(list[idx]);
		}
	}

	void search_from_list(const int* list, const int& size) {
		for (int idx = 0; idx < size; idx++) {
			output << "[search " << idx + 1 << "] ";
			search(list[idx]);
		}
	}

	void display() {
		for (int i = 0; i < size; i++) {
			std::cout << "[" << i << "]  ";
			if (table[i] == nullptr) {
				std::cout << "null ";
			}
			else {
				table[i]->display();
			}
			std::cout << "\n";
		}

	}
private:
	int hash_function(const int& key) const {
		return static_cast<int>(std::floor(size * fmod(key * A, 1.00)));
	}

};

#endif // !HashMap_h