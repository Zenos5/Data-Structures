#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
*	WARNING: You shouldnt have to change this interface file, just inherit from it.
*/

/*
*	This class specifies the methods for a car.
*
*	All cars have the following attributes:
*		Name - The car's name
*		Speed - The speed the car can attain.
*
*	The two car types have unique abilities:
*		Rocket - doubles the speed.
*		Panda - halves the speed.
*/

class CarInterface
{
public:
	CarInterface() {}
	virtual ~CarInterface() {}

	/*
	*	getName()
	*
	*	Returns the name of this car.
	*/
	virtual string getName() const = 0;

	/*
	*	getSpeed()
	*
	*	Returns the speed of this car.
	*/
	virtual int getSpeed() const = 0;
};