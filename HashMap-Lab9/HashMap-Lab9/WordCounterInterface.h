#pragma once
#include <string>
#include "HashmapInterface.h"

using namespace std;

class WordCounterInterface
{
public:
  WordCounterInterface() {};

  virtual ~WordCounterInterface() {};

  /*
   * Reads in a file
   * Builds a Hashmap that maps each word in the file to how many times the word
   *  appears in the file. (key is word, value is count).
   *
   * If file can be read in, return true. Otherwise return false.
   *  Before returning false make sure to call reset().
   *
   * A word is a string of 1 or more characters.
   * A word is only made up of alpha characters
   *  (see isalpha function http://www.cplusplus.com/reference/cctype/isalpha/).
   * The end of a word could me marked by a space, a newline, or a hyphen
   *  (' ', '\n', '-').
   * Words are case-sensitive (e.g. "The" is a different word than "the")
   */
  virtual bool loadFile(string filename) = 0;

  /*
   * Clear the map and reset any other relevant data
   */
  virtual void reset() = 0;

  /*
   * Return the sorted string of the map contents (see Hashmap toSortedString)
   */
  virtual string toString() const = 0;
};
