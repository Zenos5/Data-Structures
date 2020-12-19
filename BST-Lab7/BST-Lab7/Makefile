TARGETS = Test_Binary_Search_Tree_Numbers bst
CC = g++
CCFLAGS = -std=c++11 -g
bst: main.cpp BSTInterface.h NodeInterface.h BST.h BST.cpp Node.h Node.cpp
	$(CC) $(CCFLAGS) -o bst main.cpp BST.cpp Node.cpp
Test_Binary_Search_Tree_Numbers: Test_Binary_Search_Tree_Numbers.cpp Binary_Search_Tree.h Binary_Tree.h BTNode.h pre_order_traversal.h
	$(CC) $(CCFLAGS) -o Test_Binary_Search_Tree_Numbers Test_Binary_Search_Tree_Numbers.cpp



