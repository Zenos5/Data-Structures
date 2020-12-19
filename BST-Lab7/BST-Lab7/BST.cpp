#include "BST.h"
    /*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface * BST::getRootNode() const
	{
	    cout << "getRootNode" << endl;
		return(root);
	}

	/*
	* Attempts to add the given int to the BST tree
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool BST::add(int data)
	{
		/*
	    cout << "add" << endl;
	    Node *ptr = new Node(data);
	    ptr->leftChild = NULL; // To test that the friend relationship works
	    NodeInterface *rval = ptr->getLeftChild();
	    long value = (long)rval;
	    cout << "Added " << value << endl;
	    root = ptr;
		return true;
		*/
		return insert(root, data, root);
	}

	bool BST::insert(Node*& node, const int& data, Node*& parent)
	{
		if (node == nullptr) {
			node = new Node(data);
			node->parent = parent;
			root->parent = nullptr;
			size++;
			return true;
		}
		if (data == node->data) {
			return false; 
		}
		if (data < node->data) {
			return insert(node->leftChild, data, node);
		}
		if (data > node->data) {
			return insert(node->rightChild, data, node);
		}

		return false;
	}

	/*
	* Attempts to remove the given int from the BST tree
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool BST::remove(int data)
	{
	    cout << "remove" << endl;
		return removeNode(root, data);
	}

	bool BST::removeNode(Node*& node, const int& data)
	{
		if (node == nullptr) {
			return false;
		}
		else {
			if (data < node->data) {
				return removeNode(node->leftChild, data);
			}
			else if (data > node->data) {
				return removeNode(node->rightChild, data);
			}
			else { 
				Node* temp = node;
				if (node->leftChild == nullptr) {
					node = node->rightChild;
				}
				else if (node->rightChild == nullptr) {
					node = node->leftChild;
				}
				else {
					swap(temp, temp->leftChild);
				}
				delete temp;
				size--;
				return true;
			}
		}
	}

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void BST::clear()
	{
	    cout << "clear" << endl;
		clearTree(root);
	}

	bool BST::clearTree(Node*& node) {
		if (node != nullptr) {
			clearTree(node->leftChild);
			clearTree(node->rightChild);

			delete node;
			node = nullptr;
			size = 0;

			return true;
		}
		return true;
	}

	bool BST::swap(Node*& oldNode, Node*& node) {
		if (node->rightChild != nullptr) {
			swap(oldNode, node->rightChild);
			return true;
		}
		else {
			oldNode->data = node->data;
			oldNode = node;
			node = node->leftChild;
			return false;
		}
		return false;
	}