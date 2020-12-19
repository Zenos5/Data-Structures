#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CarInterface.h"
using namespace std;

/*
*	WARNING: It is expressly forbidden to modify any part of this document, including its name
*/
class RaceInterface
{
public:
	RaceInterface() {}
	~RaceInterface() {}

	/*
	*	addCar(string)
	*
	*	Adds a new car to the collection of cars in the race.
	*
	*	Return true if a new car was added; false otherwise.
	*   The info string should have the name, type, speed
	*/
	virtual bool addCar(string info) = 0;

	/*
	*	removeCar(string)
	*
	*	Removes the car whose name is equal to the given name.
	*
	*	Return true if a car is removed; false otherwise.
	*/
	virtual bool removeCar(string name) = 0;

	/*
	*	getCar(string)
	*
	*	Returns the memory address of a car whose name is equal to the given
	*	name.  Returns NULL if no fighter is found with the given name.
	*
	*	Return a memory address if a fighter is found; NULL otherwise.
	*/
	virtual CarInterface* getCar(string name) = 0;

	/*
	*	getSize()
	*
	*	Returns the number of cars in the race.
	*
	*	Return a non-negative integer.
	*/
	virtual int getSize() const = 0;
};