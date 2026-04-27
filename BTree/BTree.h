/*Yael Otmazgin 212531115
Linoy Bony 211820824
Exercise 04*/
#pragma once
#include<iostream>
#include "LibraryDataStructure.h"
using namespace std;

template<class T>
class BTree : public LibraryDataStructure<T>
{
private:
	class BNode
	{
	public:
		int m;		//max num of records in node +1
		T* records;
		BNode** sons;
		BNode* parent;
		int numOfRecords;
		int numOfSons;
		BNode(int _m);
		~BNode();
		bool isLeaf();
		void insert(T record);
		void remove(T record);
		void printKeys();
	};
	int m;
	BNode* root;

	void clear(BNode* current);
	void inorder(BNode* current);
	BNode* findAddNode(BNode* current, T record);
	void split(BNode* current);
	T* search(BNode* current, int key, int& counter);
public:
	BTree(int degree);
	~BTree();
	void inorder();
	void insert(T record);
	T* search(int key);
};
////////////////////////////////////////////////////////////////

template<class T>
BTree<T>::BNode::BNode(int _m) : m(_m), parent(nullptr), numOfRecords(0), numOfSons(0)
{
	// TODO: fix
	records = new T[m];
	sons = new BNode * [m + 1] {nullptr};
}

template<class T>
BTree<T>::BNode::~BNode()
{
	// TODO: fix
	if (this == nullptr)
		return;
}

template<class T>
bool BTree<T>::BNode::isLeaf()
{
	// TODO: fix
	return (numOfSons == 0);
}

template<class T>
void BTree<T>::BNode::insert(T record)
{
	// TODO: fix
	int i;
	for (i = numOfRecords - 1; i >= 0 && record < records[i]; i--)
	{
		records[i + 1] = move(records[i]);
	}
	// Insert the new record at the correct position
	records[i + 1] = std::move(record);
	numOfRecords++;
}

template<class T>
void BTree<T>::BNode::remove(T record)
{
	// TODO: fix
	int i = 0;
	// Find the index of the record to be removed
	while (record != records[i])
		i++;

	// Shift the records to remove the target record
	for (int j = i + 1; j < numOfRecords; j++)
	{
		records[j - 1] = move(records[j]);
	}

	// Decrement the number of records
	numOfRecords--;
}

template<class T>
void BTree<T>::BNode::printKeys()
{
	cout << '(';
	for (int i = 0; i < numOfRecords - 1; i++)
		cout << records[i].getKey() << ",";
	cout << records[numOfRecords - 1].getKey() << ')' << endl;
}

template<class T>
BTree<T>::BTree(int degree) :m(degree), root(nullptr)
{}

template<class T>
BTree<T>::~BTree()
{
	// TODO: fix
	clear(root);
	root = nullptr;
}

template<class T>
void BTree<T>::inorder()
{
	// TODO: fix
	if (root != nullptr)
	{
		inorder(root);
	}
}

template<class T>
void BTree<T>::insert(T record)
{
	// TODO: fix
	if (root == nullptr)
		root = new BNode(m);

	BNode* node = findAddNode(root, record);
	node->insert(record);
	split(node);
}

template<class T>
void BTree<T>::clear(BNode* current)
{
	// TODO: fix
	if (current == nullptr)
		return;

	for (int i = 0; i < current->numOfSons; ++i)
		clear(current->sons[i]);

	delete[] current->sons;
	delete current;
}

template<class T>
void BTree<T>::inorder(BNode* current)
{
	// TODO: fix
	if (current->sons[0] != nullptr)
	{
		for (int i = 0; i < current->numOfSons; i++)
		{
			if (current->sons[i] != nullptr)
				inorder(current->sons[i]);//recursive calling
			if (i < current->numOfSons - 1)
				current->printKeys();
		}
	}
	else
		current->printKeys();
}

template<class T>
typename BTree<T>::BNode* BTree<T>::findAddNode(BNode* current, T record)
{
	// TODO: fix
	if (current == nullptr)
	{
		current = new BNode(m);
		return nullptr;
	}
	else if (current->numOfRecords == 0)
	{
		return current;
	}
	else
	{
		int i = 0;
		for (i = 0; i < current->numOfRecords; i++)
		{
			if (record == current->records[i].getKey())
			{
				return nullptr; // Record already exists
			}
			else if (record < current->records[i].getKey())
			{
				break; // Found the position to insert
			}
		}

		if (current->isLeaf())
		{
			return current; // Found a leaf node to insert into
		}
		else
		{
			return findAddNode(current->sons[i], record); // Recursive call for non-leaf node
		}
	}
}

template<class T>
void BTree<T>::split(BNode* current)
{
	if (current->numOfRecords < current->m)
		return;
	else
	{
		int middleIndex = (m - 1) / 2;
		BNode* left = new BNode(current->m);
		BNode* right = new BNode(current->m);
		int i = 0;
		// Set values for the left and right nodes
		for (; i < current->numOfRecords; i++)
		{
			if (i < middleIndex)
			{
				left->records[left->numOfRecords++] = current->records[i];
			}
			else if (i > middleIndex)
			{
				right->records[right->numOfRecords++] = current->records[i];
			}
		}

		left->parent = current->parent;
		right->parent = current->parent;

		if (!current->isLeaf()) // If the current node has sons
		{
			int leftIndex = 0;
			int rightIndex = 0;

			for (int i = 0; i <= m; i++)
			{
				if (i <= middleIndex)
				{
					left->sons[leftIndex] = current->sons[i];
					left->sons[leftIndex]->parent = left;
					left->numOfSons++;
					leftIndex++;
				}
				else
				{
					right->sons[rightIndex] = current->sons[i];
					right->sons[rightIndex]->parent = right;
					right->numOfSons++;
					rightIndex++;
				}
			}
		}

		if (current == root)
		{
			BNode* newNode = new BNode(current->m);
			newNode->records[0] = current->records[middleIndex];
			newNode->numOfRecords = 1;
			newNode->sons[0] = left;
			newNode->sons[1] = right;
			left->parent = newNode;
			right->parent = newNode;
			newNode->numOfSons = 2;
			root = newNode;
			return;
		}

		current->parent->numOfSons++;
		BNode* pBNode = current->parent;

		T middeleKey = current->records[middleIndex];
		for (i = pBNode->numOfRecords - 1; i >= 0 && pBNode->records[i] > middeleKey; i--)
		{
			pBNode->records[i + 1] = pBNode->records[i];
			pBNode->sons[i + 2] = pBNode->sons[i + 1];
		}

		pBNode->records[i + 1] = middeleKey;
		pBNode->sons[i + 1] = left;
		pBNode->sons[i + 2] = right;
		pBNode->numOfRecords++;

		split(pBNode);

	}
}

template<class T>
T* BTree<T>::search(BNode* current, int key, int& counter)
{
	// TODO: fix
	if (current == nullptr)
		return nullptr; // Node not found

    counter++;
    int i = 0;
	while (i < current->numOfRecords && current->records[i].getKey() < key)
		i++;
    return (i < current->numOfRecords && current->records[i].getKey() == key)
               ? &current->records[i]                    // Found the key in the current node
               : search(current->sons[i], key, counter); // Recursively search in the appropriate child node
}

template<class T>
T* BTree<T>::search(int key) {
	int counter = 0;
	// TODO: fix
	if (root == nullptr)
		return nullptr;
	T* t = nullptr;
	t = search(root, key, counter);
	cout << "The search involved scanning " << counter << " nodes" << endl;
	return t;
}