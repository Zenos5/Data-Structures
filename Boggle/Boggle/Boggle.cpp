#include "boggle.h"
#include <time.h>

Boggle::Boggle()
{
    clear();
}

Boggle::~Boggle()
{
}

string Boggle::getBoardString()
{
    int x, y = 0;
    stringstream boardStr;
    for (y = 0; y < SIZE; y++)
    {
        for (x = 0; x < SIZE; x++)
        {
            boardStr << board[x][y];
            if (x != SIZE - 1)
                boardStr << " ";
        }
        if (y != SIZE - 1)
            boardStr << endl;
    }
    return boardStr.str();
}

void Boggle::createRandomBoard()
{
    srand(time(NULL));
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    int x, y = 0;
    for (x = 0; x < SIZE; x++)
    {
        for (y = 0; y < SIZE; y++)
        {
            board[x][y] = alpha[rand() % alpha.size()];
        }
    }
}

bool Boggle::importBoard(string file_name)
{
    ifstream ifs;
    string line;
    int x, y = 0;
    string boardValues[SIZE][SIZE];

    // Open file
    ifs.open(file_name, ifstream::in);
    if (!ifs.is_open())
    {
        cout << "file " << file_name << " failed to open" << endl;
        return false;
    }

    for (y = 0; y < SIZE; y++)
    {
        getline(ifs, line);
        if (ifs.bad() || ifs.fail())
        {
            cout << "line read fail" << endl;
            return false;
        }
        while (line[line.size() - 1] == ' ' || line[line.size() - 1] == '\n' || line[line.size() - 1] == '\r')
            line = line.substr(0, line.size() - 1);
        if (line.size() != SIZE * 2 - 1)
        {
            cout << "line wrong size: actual " << line.size() << ", expected: " << SIZE * 2 - 1 << endl;
            return false;
        }
        for (x = 0; x < SIZE; x++)
        {
            boardValues[x][y] = line[x * 2];
        }
    }

    // Check for no extra lines
    getline(ifs, line);
    if (!ifs.bad() && !ifs.fail())
    {
        cout << "too many extra lines found" << endl;
        return false;
    }

    setBoard(boardValues);
    return true;
}

bool Boggle::importDictionary(string file_name)
{
    ifstream ifs;
    string line;

    // Open file
    ifs.open(file_name, ifstream::in);
    if (!ifs.is_open())
        return false;

    while (getline(ifs, line))
    {
        while (line[line.size() - 1] == ' ' || line[line.size() - 1] == '\n' || line[line.size() - 1] == '\r')
            line = line.substr(0, line.size() - 1);
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        dictionary.push_back(line);
    }
    return true;
}

void Boggle::setMinWordLength(int length)
{
    minWordLength = length;
}

bool Boggle::isWord(string word)
{
    return findPrefix(word, 0, dictionary.size(), true);
}

bool Boggle::isPrefix(string prefix)
{
    return findPrefix(prefix, 0, dictionary.size(), false);
}

bool Boggle::findPrefix(string root, int start, int end, bool fullWordOnly)
{
    // Return false if indexes become invalid
    if (start > end)
        return false;

    int mid = (start + end) / 2;
    string middle = dictionary[mid];

    // Return true if is valid word and is at least minWordLength
    if (middle == root && root.size() >= minWordLength)
        return true;

    // Return true if is valid prefix and fullWordOnly is false
    if (!fullWordOnly && middle.substr(0, root.size()) == root)
        return true;

    // Recursive call
    if (root > middle)
        return findPrefix(root, mid + 1, end, fullWordOnly);
    else
        return findPrefix(root, start, mid - 1, fullWordOnly);
}

set<string> Boggle::solveBoard()
{
    set<string> words;
    int x, y = 0;

    // Start search at each possible starting position
    for (x = 0; x < SIZE; x++)
    {
        for (y = 0; y < SIZE; y++)
        {
            unordered_set<string> path;
            findWords("", path, words, x, y);
        }
    }

    return words;
}

void Boggle::findWords(string root, unordered_set<string> path, set<string>& wordsFound, int x, int y)
{
    // If position not on board, return
    if (x < 0 || x >= SIZE)
        return;
    if (y < 0 || y >= SIZE)
        return;

    // If position has already been visited for this root, return
    stringstream ss;
    ss << "(" << x << ", " << y << ")";
    string pos = ss.str();
    if (path.find(pos) != path.end())
        return;

    // Add position to path and add the character to root string
    path.insert(pos);
    root = root.append(board[x][y]);

    // If root is a word, add it to solution set
    if (isWord(root))
        wordsFound.insert(root);

    // If it is a prefix, recursively check all paths
    if (isPrefix(root))
    {
        findWords(root, path, wordsFound, x - 1, y); // Left
        findWords(root, path, wordsFound, x + 1, y); // Right
        findWords(root, path, wordsFound, x, y + 1); // Down
        findWords(root, path, wordsFound, x, y - 1); // Up
        findWords(root, path, wordsFound, x - 1, y - 1); // NW
        findWords(root, path, wordsFound, x + 1, y - 1); // NE
        findWords(root, path, wordsFound, x - 1, y + 1); // SW
        findWords(root, path, wordsFound, x + 1, y + 1); // SE
    }
}

void Boggle::clear()
{
    dictionary.clear();
    minWordLength = 3;
    int x, y = 0;
    for (x = 0; x < SIZE; x++)
    {
        for (y = 0; y < SIZE; y++)
        {
            board[x][y] = "a";
        }
    }
}

void Boggle::setBoard(string boardValues[SIZE][SIZE])
{
    int x, y = 0;
    for (x = 0; x < SIZE; x++)
    {
        for (y = 0; y < SIZE; y++)
        {
            board[x][y] = boardValues[x][y];
        }
    }
}