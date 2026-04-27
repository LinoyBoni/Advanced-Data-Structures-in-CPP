/*Linoy Boni 211820824
 Yael Otmazgin 212531115 */

#include "tree.h"

/*Destructor for treeList. */
treeList::~treeList()
{
	for (Tree* t : trees)
		t->~Tree();
}

/*Adds a new tree to the list with a root node containing the specified value. */
void treeList::addNewTree(string s)
{
	// Create a new Tree
	Tree* tr = new Tree();

	//Add root with specified value
	tr->addRoot(s);

	//Add the tree to the list
	trees.push_front(tr);
}

/*Removes and destroys a Tree from the list. */
void treeList::deleteTree(Tree* tree)
{
	trees.remove(tree);
	tree->~Tree();
}

/*Searches for a value in each tree and prints the subtree if found. */
void treeList::searchAndPrint(string val)
{
	Node* parent = nullptr;
	Node* curr = nullptr;

	// Iterate through the list of trees
	for (Tree* tree : trees) {
		curr = tree->search(tree->root, val, parent);

		// If the value is found, print the subtree
		if (curr != nullptr) {
			tree->print(curr);
			tree->searchAndPrintPath(tree->root, curr->content);
		}
	}
}

/*dds a response node to the specified tree. */
bool treeList::addResponse(string rt, string prnt, string res)
{
	for (Tree* tree : trees) {
		if (tree->root->content == rt) {
			return tree->addSon(prnt, res);
		}
	}
	return false;
}

/*Deletes a response node from the specified tree. */
bool treeList::delResponse(string rt, string res)
{
	bool result = false;

	for (Tree* tree : trees) {
		if (tree->root->content == rt) {

			// If the root matches the response, delete the entire tree
			if (tree->root->content == res) {
				deleteTree(tree);
				result = true;
			}
			else {
				// Delete the subtree with the specified response value
				result = tree->deleteSubTree(res);

				// Clear the content of the found node
				if (result) {
					Node* p;
					tree->search(tree->root,res,p)->content = "";
				}
			}
			break;
		}
	}
	return result;
}

/*Prints the entire tree with the specified root value. */
void treeList::printTree(string rt)
{
	for (Tree* tree : trees) {
		if (tree->root->content == rt) {
			tree->printAllTree();
		}
	}
}

/*Prints all trees in the list with tree numbers. */
void treeList::printAllTrees()
{
	int treeNumber = 1;

	// Iterate through the list of trees
	for (Tree* tree : trees) {
		cout << "Tree #" << treeNumber++ << endl;

		// Print the tree starting from its root
		tree->print(tree->root);
		cout << endl;
	}
}

/*Prints the subtree with the specified root value and starting node value. */
void treeList::printSubTree(string rt, string s)
{
	Node* child = nullptr;
	Node* parent = nullptr;

	// Iterate through the list of trees
	for (Tree* tree : trees) {
		if (tree->root->content == rt) {
			child = tree->search(tree->root, s, parent);

			// If the starting node is not found, return
			if (child == nullptr)
				return;

			cout << endl;

			// Print the subtree starting from the found node
			tree->print(child);
			tree->searchAndPrintPath(tree->root, s);
		}
	}
}
