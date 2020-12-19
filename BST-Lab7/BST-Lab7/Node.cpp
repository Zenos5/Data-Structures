#include "Node.h"
    /*
	* Returns the data that is stored in this node
	*
	* @return the data that is stored in this node.
	*/
	int Node::getData() const
	{
	    cout << "getData" << endl;
	    return(data);
	}

	/*
	* Returns the left child of this node or null if it doesn't have one.
	*
	* @return the left child of this node or null if it doesn't have one.
	*/
	NodeInterface * Node::getLeftChild() const
	{
	      cout << "getLeft" << endl;
	      return(leftChild);
	}

	/*
	* Returns the right child of this node or null if it doesn't have one.
	*
	* @return the right child of this node or null if it doesn't have one.
	*/
	NodeInterface * Node::getRightChild() const
	{
	      cout << "getRight" << endl;
	      return(rightChild);
	}
	void Node::setLeftChild(Node *ptr)
	{
	      cout << "setLeft" << endl;
	      leftChild = ptr;
	}
	void Node::setRightChild(Node *ptr)
	{
	      cout << "setRight" << endl;
	      rightChild = ptr;
	}