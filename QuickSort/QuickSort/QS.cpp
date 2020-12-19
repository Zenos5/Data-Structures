#include "QS.h"

/* Sort the elements of a QuickSort subarray using median and partition functions. */
void QS::sort(size_t left, size_t right) {
	int midIndex = 0;
	int pivotIndex = 0;
	if (right - left > 1) {
		try {
			midIndex = medianOfThree(left, right);
			if (midIndex != -1)
			{
				pivotIndex = partition(left, right, midIndex);
			}
			else
			{
				cout << "MidIndex -1" << endl;
			}
		}
		catch (...) {
			cout << "Sort Error" << endl;
		}
		if (midIndex == -1)
		{
			cout << "Sort Error" << endl;
		}
		else
		{
			sort(left, pivotIndex);
			sort(pivotIndex + 1, right);
		}
	}
	cout << "Sort Ended" << endl;
}

/*
	* sortAll()
	*
	* Sorts elements of the array.  After this function is called, every
	* element in the array is less than or equal its successor.
	*
	* Does nothing if the array is empty.
	*/
void QS::sortAll() 
{
	cout << "Sort All - End Index: " << getSize() - 1 << endl;
	sort(0, getSize() - 1);
}

/*
* medianOfThree()
*
* The median of three pivot selection has two parts:
*
* 1) Calculates the middle index by averaging the given left and right indices:
*
* middle = (left + right)/2
*
* 2) Then bubble-sorts the values at the left, middle, and right indices.
*
* After this method is called, data[left] <= data[middle] <= data[right].
* The middle index will be returned.
*
* Returns -1 if the array is empty, if either of the given integers
* is out of bounds, or if the left index is not less than the right
* index.
*
* @param left
* 		the left boundary for the subarray from which to find a pivot
* @param right
* 		the right boundary for the subarray from which to find a pivot
* @return
*		the index of the pivot (middle index); -1 if provided with invalid input
*/
int QS::medianOfThree(int left, int right) 
{
	if ((getSize() == 0) || (left >= right) || (left < 0) || (right >= getSize())) {
		return -1;
	}
	int middleIndex = 0;
	middleIndex = (left + right) / 2;
	bool exchanged;
	do {
		exchanged = false;
		if (array[left] > array[middleIndex]) {
			swap(array[left], array[middleIndex]);
			exchanged = true;
		}
		++numComparisons;
		if (array[middleIndex] > array[right]) {
			swap(array[middleIndex], array[right]);
			exchanged = true;
		}
	} while (exchanged == true);
	return middleIndex;
}

/*
* Partitions a subarray around a pivot value selected according to
* median-of-three pivot selection.  Because there are multiple ways to partition a list,
* we will follow the algorithm on page 611 of the course text when testing this function.
*
* The values which are smaller than the pivot should be placed to the left
* of the pivot; the values which are larger than the pivot should be placed
* to the right of the pivot.
*
* Returns -1 if the array is null, if either of the given integers is out of
* bounds, or if the first integer is not less than the second integer, or if the
* pivot is not within the sub-array designated by left and right.
*
* @param left
* 		the left boundary for the subarray to partition
* @param right
* 		the right boundary for the subarray to partition
* @param pivotIndex
* 		the index of the pivot in the subarray
* @return
*		the pivot's ending index after the partition completes; -1 if
* 		provided with bad input
*/
int QS::partition(int left, int right, int pivotIndex) 
{
	if ((getSize() == 0) || (left < 0) || (right >= getSize()) || (left >= right) || (pivotIndex > right) || (pivotIndex < left)) {
		return -1;
	}
	swap(array[left], array[pivotIndex]);
	size_t up = 0;
	size_t down = 0;
	up = left + 1;
	down = right - 1;
	do {
		while (array[up] <= array[left] && (up != right - 1)) {
			++up;
		}
		while (array[down] > array[left] && (down != left)) {
			--down;
		}
		if (up < down) {
			swap(array[up], array[down]);
		}
	} while (up < down);
	swap(array[left], array[down]);
	return down;
}

/*
* Produces a comma delimited string representation of the array. For example: if my array
* looked like {5,7,2,9,0}, then the string to be returned would look like "5,7,2,9,0"
* with no trailing comma.  The number of cells included equals the number of values added.
* Do not include the entire array if the array has yet to be filled.
*
* Returns an empty string, if the array is NULL or empty.
*
* @return
*		the string representation of the current array
*/
string QS::getArray() const 
{
	string arrayString = "";
	if (array == NULL || getSize() == 0)
	{
		arrayString = "";
	}
	else
	{
		for (int i = 0; i < getSize(); i++)
		{
			if (i == getSize() - 1)
			{
				arrayString += to_string(array[i]);
			}
			else
			{
				arrayString += to_string(array[i]) + ",";
			}
		}
	}
	cout << "Array: " << arrayString << endl;
	return arrayString;
}

/*
* Returns the number of elements which have been added to the array.
*/
int QS::getSize() const 
{
	return numElements;
}

/*
* Adds the given value to the end of the array starting at index 0.
* For example, the first time addToArray is called,
* the give value should be found at index 0.
* 2nd time, value should be found at index 1.
* 3rd, index 2, etc up to its max capacity.
*
* If the array is filled, do nothing.
* returns true if a value was added, false otherwise.
*/
bool QS::addToArray(int value) 
{
	if (numElements < maxCapacity) {
		array[numElements] = value;
		++numElements;
		return true;
	}
	else
	{
		return false;
	}
}

/*
* Dynamically allocates an array with the given capacity.
* If a previous array had been allocated, delete the previous array.
* Returns false if the given capacity is non-positive, true otherwise.
*
* @param
*		size of array
* @return
*		true if the array was created, false otherwise
*/
bool QS::createArray(int capacity) 
{
	if (array != nullptr) {
		delete[] array;
	}
	if (capacity <= 0)
	{
		return false;
	}
	array = new int[capacity];
	numElements = 0;
	maxCapacity = capacity;
	return true;
}

/*
* Resets the array to an empty or NULL state.
*/
void QS::clear() 
{
	delete[] array;
	array = nullptr;
	numElements = 0;
	cout << "Cleared Array" << endl;
}