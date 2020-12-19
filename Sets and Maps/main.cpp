#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <utility>
#include <time.h>
using namespace std;

int main(int argc, char* argv[]) {
    vector<string> tokens;
    set <string> unique;
    string next_line;  // Each data line
    ifstream in(argv[1]);
    string filename = argv[1];    
    for (int i = 0; i < 4; i++)
        filename.pop_back();

    //output files
    ofstream out_set(filename + "_set.txt");
    ofstream out_vector(filename + "_vector.txt");
    ofstream out_map(filename + "_map.txt");
    ofstream out_part4(filename + "_part4.txt");
    ofstream out_part5(filename + "_part5.txt");
    ofstream out_part6(filename + "_part6.txt");
    ofstream out_part7(filename + "_part7.txt");

    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for (auto& c : token) { // Remove Punctuation      
                if (isalpha(c)) {
                    nopunct += c; //tolower(c);
                }
            }
            tokens.push_back(nopunct);
            unique.insert(nopunct);
        }
    }
    cout << "Number of words " << tokens.size() << endl;
    cout << "Number of unique words " << unique.size() << endl;

    //set
    for (set<string>::iterator it = unique.begin(); it != unique.end(); ++it)
    {
        out_set << ' ' << *it << endl;
        //cout << ' ' << *it << endl;
    }
    //vector
    for (int i = 0; i < tokens.size(); i++)
    {
        out_vector << ' ' << tokens.at(i) << endl;
        //cout << ' ' << tokens.at(i) << endl;
    }
    //map
    map<string, string> wordmap;
    string last = "";
    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
        wordmap[last] = *it;
        last = *it;
    }
    for (map<string, string>::iterator it = wordmap.begin(); it != wordmap.end(); ++it)
        out_map << it->first << ", " << it->second << endl;
    //part 4
    string state = "";
    for (int i = 0; i < 100; i++) {
        out_part4 << wordmap[state] << " ";
        state = wordmap[state];
    }
    //part 5
    map<string, vector<string>> wordmap2;
    state = "";
    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
        wordmap2[state].push_back(*it);
        state = *it;
    }
    srand(time(NULL)); // this line initializes the random number generated
                   // so you dont get the same thing every time
    state = "";
    for (int i = 0; i < 100; i++) {
        int ind = rand() % wordmap2[state].size();
        out_part5 << wordmap2[state][ind] << " ";
        state = wordmap2[state][ind];
    }
    //part 6
    map<vector<string>, vector<string>> wordmap3;
    vector<string> currentstate;
    int M = 2;
    for (int i = 0; i < M; i++) {
        currentstate.push_back("");
    }
    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
        wordmap3[currentstate].push_back(*it);
        currentstate.push_back(*it);
        currentstate.erase(currentstate.begin());
    }
    currentstate.clear();
    for (int i = 0; i < M; i++) {
        currentstate.push_back("");
    }
    for (int i = 0; i < 100; i++) {
        int ind = rand() % wordmap3[currentstate].size();
        out_part6 << wordmap3[currentstate][ind] << " ";
        currentstate.push_back(wordmap3[currentstate][ind]);
        currentstate.erase(currentstate.begin());
    }
    //part 7
    map<vector<string>, vector<string>> wordmap4;
    vector<string> currentstate2;
    M = 3;
    for (int i = 0; i < M; i++) {
        currentstate2.push_back("");
    }
    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
        wordmap4[currentstate2].push_back(*it);
        currentstate2.push_back(*it);
        currentstate2.erase(currentstate2.begin());
    }
    currentstate2.clear();
    for (int i = 0; i < M; i++) {
        currentstate2.push_back("");
    }
    for (int i = 0; i < 127; i++) {
        int ind = rand() % wordmap4[currentstate2].size();
        if (i == 0)
        {
            wordmap4[currentstate2][ind][0] = toupper(wordmap4[currentstate2][ind][0]);
            out_part7 << wordmap4[currentstate2][ind];
        }
        else if (i == 126)
        {
            out_part7 << " " << wordmap4[currentstate2][ind] << ".";
        }
        else if (isupper(wordmap4[currentstate2][ind][0]))
        {
            out_part7 << ". " << wordmap4[currentstate2][ind];
        }
        else
        {
            out_part7 << " " << wordmap4[currentstate2][ind];
        }
        currentstate2.push_back(wordmap4[currentstate2][ind]);
        currentstate2.erase(currentstate2.begin());
    }
    
    in.close();
    out_set.close();
    out_vector.close();
    out_map.close();
    out_part4.close();
    out_part5.close();
    out_part6.close();
    out_part7.close();
    cout << endl;

	return 0;
}