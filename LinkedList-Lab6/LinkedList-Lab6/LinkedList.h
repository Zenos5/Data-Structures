#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "LinkedListInterface.h"

#include <sstream>
#include <string>
using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T>
{
private:
	struct Node {
		T data;
		Node* next;
	};
	Node* head;
	int listSize;
public:

	LinkedList() 
	{
		head = NULL;
		listSize = 0;
	}
	~LinkedList(void) 
	{
		while (head != NULL)
		{
			Node* current = head;
			head = head->next;
			delete current;
		}
		listSize = 0;
	}

	/*
	insertHead

	A node with the given value should be inserted at the beginning of the list.

	Do not allow duplicate values in the list.
	*/
	virtual void insertHead(T value)
	{
		bool duplicate = false;
		for (Node* ptr = head; ptr != NULL; ptr = ptr->next)
		{
			if (ptr->data == value)
			{
				duplicate = true;
			}
		}
		if (!duplicate)
		{
			Node* newNode = new Node;
			newNode->data = value;
			newNode->next = head;
			head = newNode;
			listSize++;
		}
		cout << "Inserted at Head" << endl;
	}

	/*
	insertTail

	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	virtual void insertTail(T value)
	{
		bool duplicate = false;
		for (Node* ptr = head; ptr != NULL; ptr = ptr->next)
		{
			if (ptr->data == value)
			{
				duplicate = true;
			}
		}
		Node* newNode = new Node;
		newNode->data = value;
		newNode->next = NULL;
		if (head == NULL)
		{
			head = newNode;
			listSize++;
		}
		else if (!duplicate)
		{
			Node* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newNode;
			listSize++;
		}
		cout << "Inserted at Tail" << endl;
	}

	/*
	insertAfter

	A node with the given value should be inserted immediately after the
	node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	virtual void insertAfter(T value, T insertionNode)
	{
		bool duplicate = false;
		bool present = false;
		for (Node* ptr = head; ptr != NULL; ptr = ptr->next)
		{
			if (ptr->data == value)
			{
				duplicate = true;
			}
			if (ptr->data == insertionNode)
			{
				present = true;
			}
		}
		if (present)
		{
			Node* insertNode = head;
			while (insertNode->data != insertionNode)
			{
				insertNode = insertNode->next;
			}
			if (!duplicate)
			{
				Node* newNode = new Node;
				newNode->data = value;
				newNode->next = insertNode->next;
				insertNode->next = newNode;
				listSize++;
			}
		}
		cout << "Inserted Node after " << insertionNode << endl;
	}

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	virtual void remove(T value)
	{
		int size = 0;
		if (head == NULL)
		{
			cout << "List is Empty" << endl;
		}
		else if (head->data == value)
		{
			Node* tmp = head->next;
			delete head;
			head = tmp;
			listSize--;
		}
		else
		{
			for (Node* ptr = head; ptr != NULL; ptr = ptr->next)
			{
				if (size < listSize - 1)
				{
					if (ptr->next->data == value)
					{
						Node* newNode = ptr->next;
						ptr->next = newNode->next;
						delete newNode;
						listSize--;
					}
				}
				size++;
			}
		}
		cout << "Finished removal of node" << endl;
	}

	/*
	clear

	Remove all nodes from the list.
	*/
	virtual void clear()
	{
		/*
		for (Node* ptr = head; ptr != NULL; ptr = ptr->next)
		{
			Node* newNode = ptr;
			ptr = ptr->next;
			delete newNode;
		}
		*/

		Node* current = head;
		Node* next;
		while (current != NULL)
		{
			next = current->next;
			delete current;
			current = next;
		}
		head = NULL;
		listSize = 0;
		cout << "Finished Clear" << endl;
	}

	/*
	at

	Returns the value of the node at the given index. The list begins at
	index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	virtual T at(int index)
	{
		int placement = 0;
		if (index >= listSize || index < 0)
		{
			throw std::out_of_range("Index is Out of Range");
		}
		Node* ptr = head;
		while (placement < index)
		{
			ptr = ptr->next;
			placement++;
		}
		return ptr->data;
	}

	/*
	size

	Returns the number of nodes in the list.
	*/
	virtual int size()
	{
		return listSize;
	}

	/*
	toString

	Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
	There should be no trailing space at the end of the string

	For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
	"1 2 3 4 5"
	*/
	virtual string toString()
	{
		string orderedList = "";
		stringstream ss("");
		string nodeData = "";
		int numData;
		for (Node* ptr = head; ptr != NULL; ptr = ptr->next)
		{
			ss << ptr->data;
			ss >> nodeData;
			if (ptr == head)
			{
				//orderedList += ptr->data;
				orderedList += nodeData;
				cout << ptr->data;
			}
			else
			{
				//orderedList += " " + ptr->data;
				orderedList += " " + nodeData;
				cout << " " << ptr->data;
			}
			ss.clear();
			nodeData = "";
		}
		cout << endl;
		cout << "Finished ToString" << endl;
		return orderedList;
	}
};
#endif