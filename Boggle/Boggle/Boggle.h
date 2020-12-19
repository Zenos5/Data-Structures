#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <vector>

#define SIZE 5

using namespace std;

class Boggle
{
private:
    string board[SIZE][SIZE]; // A 2-dimensional array of strings representing the boggle board
    vector<string> dictionary; // A collection of dictionary words in alphabetical order
    int minWordLength; // The minimum word length of words to find in boggle

    /*
     * The recursive function to find words on the boggle board
     * @param root - the current word that you're building as you visit positions on the board
     * @param path - a collection of positions that you have visited while building your current word
     * @param wordsFound - a collection of all words that have been found so far
     * @param x - the x-coordinate in the position to visit
     * @param y - the y-coordinate in the position to visit
     */
    void findWords(string root, unordered_set<string> path, set<string>& wordsFound, int x, int y);

    /*
     * Clear the dictionary
     * Reset minWordLength to 3
     * Set all positions on the board to "a"
     */
    void clear();

    /*
     * Copy the values passed in to the board array
     */
    void setBoard(string boardValues[SIZE][SIZE]);

    /*
     * Is the root a valid prefix, a valid word, or neither?
     * @param root - the string to test if it is a valid word/prefix in the dictionary
     * @param start - the lower-bound index of the dictionary to check
     * @param end - the higher-bound index of the dictionary to check
     * @param fullWordOnly - if this is true, then only return true if root is a word in the dictionary
     * @return - return true if root is found to be a valid word or prefix in the dictionary.
     *  In the case that fullWordOnly is true, then return false if it is not a valid word in the dictionary
     */
    bool findPrefix(string root, int start, int end, bool fullWordOnly);

public:
    /*
     * Initialize everything (use the clear function)
     */
    Boggle();

    // Destructor
    ~Boggle();

    /*
     * Get a string representation of the board
     * Every cell should be separated by a space
     * No space at the end of each line
     * No extra line at the end of the string
     */
    string getBoardString();

    /*
     * Generate a random board and store it in the board array
     */
    void createRandomBoard();

    /*
     * Read in a board from a file and store it in the board array
     * If for some reason the import fails, then don't overwrite current board
     * If the import is successful, use the setBoard function to store to board array
     */
    bool importBoard(string file_name);

    /*
     * Read in the dictionary
     * @param file_name - dictionary file
     *   This file should have one word per row and should already be sorted in alphabetical order
     */
    bool importDictionary(string file_name);

    /*
     * Set minWordLength
     * This value should not impact the values in the dictionary, just the values returned by solveBoard
     */
    void setMinWordLength(int length);

    /*
     * Return true if word is found in the dictionary
     * Use findPrefix and set fullWordOnly to true
     */
    bool isWord(string word);

    /*
     * Return true if prefix is found at the start of any word in the dictionary
     * Use findPrefix and set fullWordOnly to false
     */
    bool isPrefix(string prefix);

    /*
     * Return a collection of words found on the boggle board
     * Use findWords. Start with root="", path = empty set, (x,y) = starting position
     *   You'll need to call findWords for every possible starting position on the board
     */
    set<string> solveBoard();
};