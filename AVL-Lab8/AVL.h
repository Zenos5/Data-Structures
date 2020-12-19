#pragma once
#include "AVLInterface.h"
#include "Node.h"

class AVL : public AVLInterface
{
public:
	AVL()
	{
		root = NULL;
		size = 0;
	}
	virtual ~AVL()
	{
		clear();
	}

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface* getRootNode() const;

	/*
	* Attempts to add the given int to the BST tree
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data);

	bool insert(Node*& node, const int& data, Node*& parent);

	/*
	* Attempts to remove the given int from the BST tree
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data);

	bool removeNode(Node*& node, const int& data);

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear();

	bool clearTree(Node*& node);

	bool swap(Node*& oldNode, Node*& node);

	void rotateRight(Node*& localRoot);

	void rotateLeft(Node*& localRoot);

	void rebalanceLeft(Node*& localRoot);
	
	void rebalanceRight(Node*& localRoot);
protected:
	Node* root;
	size_t size;
	bool increase;
	bool decrease;
};
