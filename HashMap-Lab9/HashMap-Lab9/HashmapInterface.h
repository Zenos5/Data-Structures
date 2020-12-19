//YOU MAY NOT MODIFY THIS DOCUMENT
#pragma once
#include <string>

using namespace std;

class HashmapInterface
{
public:
	HashmapInterface() {}
	virtual ~HashmapInterface() {}

	/*
	 * Insert a key/value pair into the map
	 *  If key is not in the map yet, add new key/value pair to map
	 *  If key is already in the map, replace old value with new value
	 */
	virtual void insert(string key, int value) = 0;

	/*
	 * Test if the key exists in the map
	 *  Return true if one of the nodes in the map has the given key, false otherwise
	 */
	virtual bool contains(string key) const = 0;

	/*
	 * Return the value associated with the given key in the map
	 *  Throw invalid_argument exception if key is not in map
	 */
	virtual int get(string key) const = 0;

	/*
	 * Return a reference to a value associated with the given key in the map
	 *  This will allow you use syntax such as map['pig'] to get the value
	 *   for the given key
	 *  This will also allow you use sytnax such as map['pig']=10 to set/update
	 *   the value for the given key
	 *  If the node with the given key is found in the map, return that node's value
	 *  If the ndoe with the given key is not found in the map, insert a new node with
	 *   the given key and a value of 0 into the map, then return newNode->value
	 */
	virtual int& operator [](string key) = 0;

	/*
	 * Remove the node with given key from the map
	 *  Return true if node is found and removed
	 *  Return false if the key does not exist in the map
	 */
	virtual bool remove(string key) = 0;

	/*
	 * Reset map to empty
	 *  Deallocate all memory
	 */
	virtual void clear() = 0;

	/*
	 * Return string representation of map
	 *  Each row of the string representation should represent a list of key/values
	 *  in a single bucket.
	 *
	 *  An empty bucket should look like this:
	 *  [0]
	 *
	 *  A bucket with a single key/value pair should look like this:
	 *  [0] pig => 10
	 *
	 *  And a bucket with multiple key/value pairs should look like this:
	 *  [0] pig => 10, moose => 3
	 *
	 *  Each bucket should be on one line. Buckets should be in numerical order
	 *  starting at 0 and going up to BUCKETS-1. For example, if BUCKETS is 5
	 *  the string might look like this:
	 *  [0]
	 *  [1] rock => 4, bacon => 17
	 *  [2] hippie => 8
	 *  [3]
	 *  [4] dagger => 2, wrench => 1, pipe => 4
	 *
	 *  There should be no trailing spaces or commas. Lines should end with single
	 *  newline character \n
	 */
	virtual string toString() const = 0;

	/*
	 * Return number of keys in map
	 */
	virtual int size() const = 0;
};
