/** Program to test binary tree class using numbers*/

#include <string>
#include <iostream>
#include <fstream>
#include "Binary_Search_Tree.h"
#include "pre_order_traversal.h"

using namespace std;

int main() 
{

  Binary_Search_Tree<double> the_tree;
  double value;
  cout << "Enter a number to add (zero to exit)"<<endl;
  while (cin >> value) {
    if (value == 0) break;
    the_tree.insert(value);
    cout << "Preorder Traversal"<<endl;
    pre_order_traversal(the_tree, cout, 0);
    cout << "Enter a number to add (zero to exit)"<<endl;
  }
  cin.clear();
  cout << "Enter a number to erase (zero to exit)"<<endl;
  while (cin >> value) {
    if (value == 0) break;
    the_tree.erase(value);
    cout << "Preorder Traversal"<<endl;
    pre_order_traversal(the_tree, cout, 0);
    cout << "Enter a number to erase (zero to exit)"<<endl;
  }
}


  
