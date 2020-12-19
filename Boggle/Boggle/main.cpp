#include "boggle.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Usage: ./boggle <board_file> <dictionary_file> <min_word_length>" << endl;
        return 1;
    }

    // Default board (should be all "a")
    Boggle boggle;
    cout << boggle.getBoardString() << endl << endl;

    // Random board
    boggle.createRandomBoard();
    cout << boggle.getBoardString() << endl << endl;

    // Import board (if import fails, then random board will be used)
    bool success = boggle.importBoard(argv[1]);
    if (success)
        cout << "success importing " << argv[1] << endl;
    else
        cout << "error importing " << argv[1] << endl;

    // Import dictionary and set min word length
    /*boggle.importDictionary(argv[2]);
    stringstream ss(argv[3]);
    int minWordLength = 3;
    ss >> minWordLength;
    boggle.setMinWordLength(minWordLength);
    */

    // Test isWord and isPrefix
    string tests[] = { "a", "and", "aard", "aardvark", "aaard", "mil", "mlead", "zymurgy", "zymurg", "zymany" };
    for (int i = 0; i < 10; i++)
    {
        bool isWord = boggle.isWord(tests[i]);
        if (isWord)
            cout << tests[i] << " is a word" << endl;
        else
            cout << tests[i] << " is NOT a word" << endl;
        bool isPrefix = boggle.isPrefix(tests[i]);
        if (isPrefix)
            cout << tests[i] << " is a prefix" << endl;
        else
            cout << tests[i] << " is NOT a prefix" << endl;
    }
    cout << endl;

    // Solve the board
    cout << boggle.getBoardString() << endl << endl;
    set<string> words = boggle.solveBoard();

    // Print solution
    cout << "Found " << words.size() << " words:" << endl;
    for (set<string>::iterator it = words.begin(); it != words.end(); ++it)
    {
        cout << *it << endl;
    }
}