#include "Car.h"
string Car::getName() const {
	cout << "In Car getName" << endl;
	return name;
};

int Car::getSpeed() const {
	return (speed);
};

std::ostream& operator<< (std::ostream& out, const Car& ocar)
{
	// Since operator<< is a friend of the Car class, we can access Car's members directly.
	out << "Car(" << ocar.name << ", " << ocar.speed << ")";

	return out;
}