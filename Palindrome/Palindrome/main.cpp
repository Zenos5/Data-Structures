#include <iostream>
#include <string>
#include <stack>
using namespace std;
int main()
{
    string trypal("this is a palap a si siht");

    stack<char> mychars;
    for (int i = 0; i < trypal.length(); i++) {
        mychars.push(trypal[i]);
    }

    bool ispal = true;
    for (int i = 0; i < trypal.length(); i++) {
        char next = mychars.top();
        mychars.pop();
        cout << "Comparing " << trypal[i] << " " << next << endl;
        if (trypal[i] != next) {
            cout << "Not a Palindrome" << endl;
            ispal = false;
            break;
        }
    }
    if (ispal) {
        cout << "Is a Palindrome";
    }

    return 0;
}