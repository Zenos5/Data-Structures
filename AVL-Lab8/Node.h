#pragma once
#include "NodeInterface.h"
#include <cstddef>
using namespace std;

class Node : public NodeInterface
{
	friend class AVL; // Allow BST to access data members
public:
	Node(int value)
	{
		data = value;
		leftChild = NULL;
		rightChild = NULL;
		balance = BALANCED;
		parent = NULL;
	}
	~Node() {}

	/*
	* Returns the data that is stored in this node
	*
	* @return the data that is stored in this node.
	*/
	int getData() const;

	/*
	* Returns the left child of this node or null if it doesn't have one.
	*
	* @return the left child of this node or null if it doesn't have one.
	*/
	NodeInterface* getLeftChild() const;

	/*
	* Returns the right child of this node or null if it doesn't have one.
	*
	* @return the right child of this node or null if it doesn't have one.
	*/
	NodeInterface* getRightChild() const;
	void setLeftChild(Node* ptr);
	void setRightChild(Node* ptr);
	int getHeight();
protected:
	Node* leftChild;
	Node* rightChild;
	Node* parent;
	int data;
	enum balanceType {LEFT_HEAVY = -1, BALANCED = 0, RIGHT_HEAVY = 1};
	balanceType balance;
};
