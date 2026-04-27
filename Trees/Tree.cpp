/*Linoy Boni 211820824
 Yael Otmazgin 212531115 */

#include "tree.h"

/*Searches for a node with the specified value in the tree. */
Node* Tree::search(Node* p, string val, Node*& parent)
{
	// Base case: Value not found in current subtree.
	if (p == nullptr) {
		return nullptr;
	}

	// Found the node with the desired value.
	if (p->content == val) {
		return p;
	}

	// Traverse son nodes, updating parent pointer. (for on Node* type)
	for (Node* son : p->responses) {
		parent = p;
		Node* result = search(son, val, parent);

		// Return result if value found in the son subtree.
		if (result != nullptr) {
			return result;
		}
	}

	// Value not found in current or son subtrees.
	return nullptr;
}

/*Searches for a value in the discussion tree and prints the path. */
bool Tree::searchAndPrintPath(Node* p, string val)
{
	// Initialize pointers for current node (temp) and its parent
	Node* parent = nullptr;
	Node* temp = search(p, val, parent);

	// If the value is not found in the tree
	if (temp == nullptr) {
		return false;
	}

	// Traverse the path from the found node to the p
	while (temp != nullptr && temp != p) {
		// Print the content of each node in the path
		cout << temp->content << "=>";

		// Move to the parent node in the path
		temp = search(p, parent->content, parent);
	}

	// Print the content
	cout << temp->content << endl;

	// Path successfully printed
	return true;
}

/*Prints the discussion tree from a node with indentation. */
void Tree::print(Node* p, int level)
{
	// Base case: exit if the node is nullptr
	if (!p) return;

	// Print node content with indentation
	cout << string(level * 3, ' ') << p->content << endl;

	// Recursively print child nodes
	for (Node* child : p->responses) {
		print(child, level + 1);
	}
}

/*Deletes the subtree rooted at a given node. */
void Tree::deleteAllSubTree(Node* t)
{
	if (t) {
		// Recursively delete each child node
		for (Node* child : t->responses) {
			deleteAllSubTree(child);
			delete child;
		}

		t->responses.clear(); // Clear the responses list after deletion
	}
}

/*Sets a new root with the specified value, clearing the existing tree. */
void Tree::addRoot(string newval)
{
	// Clear existing tree
	deleteAllSubTree(root);

	// Create a new root
	root = new Node(newval);
}

/*Adds a response to the discussion tree under the specified parent node. */
bool Tree::addSon(string fatherdiscussion, string newresponse)
{
	// Find the parent node in the tree
	Node* parent = search(root, fatherdiscussion, parent);

	// If parent exists, add a new response and update the isLeaf flag
	if (parent) {
		parent->responses.push_back(new Node(newresponse));
		parent->isLeaf = false;
		return true;
	}

	// Return false if parent is not found
	return false;
}

/*Prints the subtree rooted at the node with the specified value. */
bool Tree::printSubTree(Node* curr, string val)
{
	Node* subtreeRoot = search(curr, val, subtreeRoot);

	// Print subtree if found, return true; otherwise, return false
	return (subtreeRoot) ? (print(subtreeRoot), true) : false;
}

/*Deletes the subtree rooted at the node with the specified value. */
bool Tree::deleteSubTree(string val)
{
	Node* parent = search(root, val, parent);

	// If parent exists, delete entire subtree and set parent to nullptr
	if (parent) {
		deleteAllSubTree(parent);
		parent = nullptr;
		return true;
	}

	// Return false if parent is not found
	return false;
}




