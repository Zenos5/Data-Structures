#include "AVL.h"
#include <iostream>

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface* AVL::getRootNode() const
	{
		//cout << "getRootNode" << endl;
		return(root);
	}

	/*
	* Attempts to add the given int to the BST tree
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool AVL::add(int data)
	{
		return insert(root, data, root);
	}

	bool AVL::insert(Node*& node, const int& data, Node*& parent)
	{
		if (node == nullptr) {
			node = new Node(data);
			size++;
			increase = true;
			return true;
		}
		else if (data < node->data) {
			bool returnVal = insert(node->leftChild, data, node);
			if (increase)
			{
				Node* localRoot = node;
				switch (localRoot->balance)
				{
					case Node::BALANCED :
						//local root is now left heavy
						localRoot->balance = Node::LEFT_HEAVY;
						break;
					case Node::RIGHT_HEAVY :
						//local root is now right heavy
						localRoot->balance = Node::BALANCED;
						//Overall height of local root remains the same
						increase = false;
						break;
					case Node::LEFT_HEAVY :
						rebalanceLeft(node);
						increase = false;
						break;
				}
			}
			return returnVal;
		}
		else if (data > node->data) {
			bool returnVal = insert(node->rightChild, data, node);
			if (increase)
			{
				Node* localRoot = node;
				switch (localRoot->balance)
				{
				case Node::BALANCED:
					//local root is now left heavy
					localRoot->balance = Node::RIGHT_HEAVY;
					break;
				case Node::LEFT_HEAVY:
					//local root is now right heavy
					localRoot->balance = Node::BALANCED;
					//Overall height of local root remains the same
					increase = false;
					break;
				case Node::RIGHT_HEAVY:
					//local root is critically unbalanced;
					rebalanceRight(node);
					increase = false;
					break;
				}
			}
			return returnVal;
		}
		else
		{
			increase = false;
			return false;
		}	
	}

/*
* Attempts to remove the given int from the BST tree
*
* @return true if successfully removed
* @return false if remove is unsuccessful(i.e. the int is not in the tree)
*/
bool AVL::remove(int data)
{
	//cout << "remove" << endl;
	return removeNode(root, data);
}

bool AVL::removeNode(Node*& node, const int& data)
{
	if (node == nullptr) {
		decrease = false;
		return false;
	}
	else {
		if (data < node->data) {
			cout << "if (data < node->data)" << endl;
			bool returnVal = removeNode(node->leftChild, data);
			if (decrease)
			{
				cout << "Rotated in <" << endl;
				Node* localRoot = node;
				switch (localRoot->balance)
				{
				case Node::BALANCED:
					//local root is now right heavy
					localRoot->balance = Node::RIGHT_HEAVY;
					decrease = false;
					break;
				case Node::LEFT_HEAVY:
					//local root is now balanced
					localRoot->balance = Node::BALANCED;
					//Overall height of local root remains the same
					decrease = true;
					break;
				case Node::RIGHT_HEAVY:
					rebalanceRight(node);
					//decrease = false;
					break;
				}
			}
			return returnVal;
		}
		else if (data > node->data) {
			cout << "if (data > node->data)" << endl;
			bool returnVal = removeNode(node->rightChild, data);
			if (decrease)
			{
				cout << "Rotated in >" << endl;
				Node* localRoot = node;
				switch (localRoot->balance)
				{
				case Node::BALANCED:
					//local root is now left heavy
					localRoot->balance = Node::LEFT_HEAVY;
					decrease = false;
					break;
				case Node::RIGHT_HEAVY:
					//local root is now balanced
					localRoot->balance = Node::BALANCED;
					//Overall height of local root remains the same
					decrease = true;
					break;
				case Node::LEFT_HEAVY:
					rebalanceLeft(node);
					//decrease = false;
					break;
				}
			}
			return returnVal;
		}
		else {
			cout << "if (data == node->data)" << endl;
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
			decrease = true;
			removeNode(root, data);
			return true;
		}
	}
}

/*
* Removes all nodes from the tree, resulting in an empty tree.
*/
void AVL::clear()
{
	cout << "clear" << endl;
	clearTree(root);
}

bool AVL::clearTree(Node*& node) {
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

bool AVL::swap(Node*& oldNode, Node*& node) {
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

void AVL::rotateRight(Node*& localRoot)
{
	Node* temp = localRoot->leftChild;
	localRoot->leftChild = temp->rightChild;
	temp->rightChild = localRoot;
	localRoot = temp;
}

void AVL::rotateLeft(Node*& localRoot)
{
	Node* temp = localRoot->rightChild;
	localRoot->rightChild = temp->leftChild;
	temp->leftChild = localRoot;
	localRoot = temp;
}

void AVL::rebalanceLeft(Node*& localRoot)
{
	Node* node = localRoot;
	Node* left_child = localRoot->leftChild;
	if (left_child->balance == Node::RIGHT_HEAVY)
	{
		Node* left_right_child = left_child->rightChild;
		if (left_right_child->balance == Node::LEFT_HEAVY)
		{
			left_child->balance = Node::BALANCED;
			left_right_child->balance = Node::BALANCED;
			node->balance = Node::RIGHT_HEAVY;
		}
		else if (left_right_child->balance == Node::BALANCED)
		{
			left_child->balance = Node::BALANCED;
			left_right_child->balance = Node::BALANCED;
			node->balance = Node::BALANCED;
		}
		else
		{
			left_child->balance = Node::LEFT_HEAVY;
			left_right_child->balance = Node::BALANCED;
			node->balance = Node::BALANCED;
		}
		rotateLeft(localRoot->leftChild);
	}
	else
	{
		left_child->balance = Node::BALANCED;
		node->balance = Node::BALANCED;
	}
	rotateRight(localRoot);
}

void AVL::rebalanceRight(Node*& localRoot)
{
	Node* node = localRoot;
	Node* right_child = localRoot->rightChild;
	if (right_child->balance == Node::LEFT_HEAVY)
	{
		Node* right_left_child = right_child->leftChild;
		if (right_left_child->balance == Node::RIGHT_HEAVY)
		{
			right_child->balance = Node::BALANCED;
			right_left_child->balance = Node::BALANCED;
			node->balance = Node::LEFT_HEAVY;
		}
		else if (right_left_child->balance == Node::BALANCED)
		{
			right_child->balance = Node::BALANCED;
			right_left_child->balance = Node::BALANCED;
			node->balance = Node::BALANCED;
		}
		else
		{
			right_child->balance = Node::RIGHT_HEAVY;
			right_left_child->balance = Node::BALANCED;
			node->balance = Node::BALANCED;
		}
		rotateRight(localRoot->rightChild);
	}
	else
	{
		right_child->balance = Node::BALANCED;
		node->balance = Node::BALANCED;
	}
	rotateLeft(localRoot);
}