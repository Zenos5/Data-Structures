#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <utility>
using namespace std;
int main(int argc, char* argv[])
{
    // Sets
    set <string> strset;
    strset.insert("bug");
    strset.insert("horse");
    strset.insert("horse");
    set<string>::iterator findit;
    findit = strset.find("horse");
    cout << "Found horse " << *findit << endl;
    for (set<string>::iterator it = strset.begin(); it != strset.end(); ++it)
        cout << ' ' << *it;
    cout << endl;

    vector<string> tokens;
    set <string> unique;
    string next_line;  // Each data line
    ifstream in(argv[1]);
    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for (auto& c : token) { // Remove Punctuation      
                if (isalpha(c)) {
                    nopunct += c;
                }
            }
            tokens.push_back(nopunct);
            unique.insert(nopunct);
        }
    }
    cout << "Number of words " << tokens.size() << endl;
    cout << "Number of unique words " << unique.size() << endl;
    for (set<string>::iterator it = unique.begin(); it != unique.end(); ++it)
        cout << ' ' << *it;
    cout << endl;



    // pairs
    pair <string, int> mypair;
    mypair.first = "Hello";
    mypair.second = 8;
    cout << mypair.first << " " << mypair.second << endl;
    set <pair <string, int>> pairset;
    pairset.insert(mypair);
    set<pair <string, int>>::iterator findpair;
    findpair = pairset.find(mypair);
    cout << "found First " << findpair->first << " second " << findpair->second << endl;

    // maps
    map <string, int> wordcount;
    wordcount["foo"] = 5;
    cout << "wordcount for foo " << wordcount["foo"] << endl;
    wordcount.insert(mypair);
    cout << "wordcount for Hello " << wordcount["Hello"] << endl;
    wordcount.clear();
    for (auto s : tokens) {
        wordcount[s]++;
    }
    for (map<string, int>::iterator it = wordcount.begin(); it != wordcount.end(); ++it)
        cout << it->first << ' ' << it->second << endl;
    cout << endl;
}