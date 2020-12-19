#include "Hashmap.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <queue>

/*
     * Return a hash code (bucket index) for a given key
     *  Must return a value >= 0 and < BUCKETS
     *  This can be done by generating a hash code and returning "hashcode % BUCKETS"
     *  Try to make your hash function so that the distribution is uniform over all buckets
     */
unsigned int Hashmap::hash(string key) const
{
    unsigned int hashcode = 0;
    for (int i = 0; i < key.size(); i++)
    {
        hashcode += key.at(i);
    }
    hashcode %= BUCKETS;
    return hashcode;
}

string Hashmap::toSortedString() const
{
    stringstream ss;
    priority_queue<Node*, vector<Node*>, NodeCompare> nodeHeap;
    for (int i = 0; i < BUCKETS; i++)
    {
        // Iterate through each bucket. Use nodeHeap.push to push all Node* onto heap.
    }
    while (!nodeHeap.empty())
    {
        Node* top = nodeHeap.top(); // Get top node (next node in sorted order)
        ss << top->key << " => " << top->value << endl; // Add node data to stringstream
        nodeHeap.pop(); // Pop it off
    }
    return ss.str();
}