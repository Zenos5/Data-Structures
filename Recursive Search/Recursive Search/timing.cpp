#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <ctime>
#include <math.h>
using namespace std;

int search(int sval, vector <int>& svec, int spos) {
    if (svec[spos] == sval)
        return spos;
    if (spos >= svec.size())
        return -1;
    return search(sval, svec, spos + 1);
}
template<typename Item_Type>
int binary_search(const std::vector<Item_Type>& items,
    int first, int last, const Item_Type& target) {
    if (first > last)
        return -1;     // Base case for unsuccessful search.
    else {
        int middle = (first + last) / 2;  // Next probe index.
        if (target == items[middle])
            return middle;   // Base case for successful search.
        else if (target < items[middle])
            return binary_search(items, first, middle - 1, target);
        else
            return binary_search(items, middle + 1, last, target);
    }
}

int main()
{
    clock_t oldtime, newtime;
    double seconds;
    vector <int> myvec;

    int vecsize;
    cout << "Enter the size of the vector" << endl;
    cin >> vecsize;
    // Initialize the vector with random values
    for (int i = 0; i < vecsize; i++) {
        int nextval = rand();
        myvec.push_back(nextval);
    }
    // Print out the vector values
    /*for(auto val : myvec) {
      cout << val<< " ";
    }
    */
    cout << endl;
    cout << "Enter the value to search for" << endl;
    int value;
    cin >> value;
    oldtime = clock();
    cout << "Search Returned " << search(value, myvec, 0) << endl;
    newtime = clock();
    seconds = (double)(newtime - oldtime) / CLOCKS_PER_SEC;
    cout << "Took " << seconds << endl;
    // Now sort the vector
    sort(myvec.begin(), myvec.end());
    // Print out the sorted vector values
    /*for(auto val : myvec) {
      cout << val<< " ";
    }
    */
    cout << endl;
    // Now search in the sorted vector
    oldtime = clock();
    cout << "Binary Search " << binary_search(myvec, 0, myvec.size() - 1, value) << endl;
    newtime = clock();
    seconds = (double)(newtime - oldtime) / CLOCKS_PER_SEC;
    cout << "Took " << seconds << endl;
}