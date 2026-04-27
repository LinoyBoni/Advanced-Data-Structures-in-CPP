/*Linoy Boni 211820824
 Yael Otmazgin 212531115 */

#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;

class Node;

//Node: each Node in the discussion tree
class Node
{
	void removeSonValue(string v);
public:
	list<Node*> responses;
	string content;
	bool isLeaf;
	Node(string v)
	{
		isLeaf = true;
		content = v;
	}
	friend class Tree;
};

//Tree: the discussion Tree
class Tree
{
	Node* root;
	Node* search(Node* p, string val, Node*& parent); 

	//returns Node t where the string equals val. If t has a prent, the pointer parent will contain its address. 

	bool searchAndPrintPath(Node* p, string val);
	void print(Node* p, int level = 0);
public:
	Tree() { root = NULL; }
	~Tree() {
		deleteAllSubTree(root);
		root = 0;
	}
	void deleteAllSubTree(Node* t);
	void addRoot(string newval);
	bool addSon(string fatherdiscussion, string newresponse);

	bool search(string val)
	{
		Node* parent;
		if (search(root, val, parent))
		{
			cout << root->content << endl;
			return true;
		}	
		return false;
	}
	bool searchAndPrintPath(string val)
	{
		bool flag = searchAndPrintPath(root, val);
		return flag;
	}

	void printAllTree() { print(root); }
	void printSubTree(string val) { printSubTree(root, val); }
	bool printSubTree(Node* curr, string val);
	bool deleteSubTree(string val);
	friend class treeList;
};

class treeList
{
	list<Tree*> trees;

public:
	treeList() {}
	~treeList();
	void addNewTree(string s);
	void deleteTree(Tree*);
	void searchAndPrint(string val);
	bool addResponse(string rt, string prnt, string res);
	bool delResponse(string rt, string res);
	void printTree(string rt);
	void printAllTrees();
	void printSubTree(string rt, string s);
};

