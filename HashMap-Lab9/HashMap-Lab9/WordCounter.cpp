#include "WordCounter.h"

bool WordCounter::loadFile(string filename)
{
  ifstream ifs;
  ifs.open(filename);
  if(!ifs.is_open())
    return false;

  string line;
  while(getline(ifs, line))
  {
    if(ifs.bad() || ifs.fail())
    {
      reset();
      return false;
    }
    string word = "";
    string::iterator it;
    for(it=line.begin(); it != line.end(); ++it)
    {
      char c = *it;
      if(c == ' ' || c == '\n' || c == '-')
      {
        if(word != "")
          addWordToMap(word);
        word = "";
      }
      else if(isalpha(c))
      {
        word += c;
      }
    }
    if(word != "")
      addWordToMap(word);
  }

  ifs.close();

  return true;
}

void WordCounter::reset()
{
  map.clear();
}

string WordCounter::toString() const
{
  return map.toSortedString();
}

void WordCounter::addWordToMap(string word)
{
  if(map.contains(word))
    map[word]++;
  else
    map[word]=1;
}
