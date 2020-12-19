#pragma once
#include <fstream>
#include "WordCounterInterface.h"
#include "Hashmap.h"

using namespace std;

class WordCounter: public WordCounterInterface
{
private:
  Hashmap map;
  void addWordToMap(string word);
public:
  WordCounter() {};
  ~WordCounter() {};
  bool loadFile(string filename);
  void reset();
	string toString() const;
};
