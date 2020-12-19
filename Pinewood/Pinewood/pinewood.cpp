#include <iostream>
#include <fstream>
#include <sstream>
#include "Race.h"
#include "Car.h"


int main() {

	Race* rptr = new Race();

	Car* testcar = new Panda("testy", 300);
	cout << "Created a car " << *testcar << endl;

	cout << "Start Size should be zero " << rptr->getSize() << endl;
	rptr->addCar("Speedy R 20");
	cout << "Size should be 1 " << rptr->getSize() << endl;
	rptr->addCar("Slow P 10");
	cout << "Size should be 2 " << rptr->getSize() << endl;
	rptr->getSize();
	CarInterface* car1 = rptr->getCar("Speedy");
	CarInterface* car2 = rptr->getCar("Slow");
	cout << "Compare " << car1->getSpeed() << " " << car2->getSpeed() << endl;
	if (car1->getSpeed() > car2->getSpeed()) {
		cout << car1->getName() << " Won!" << endl;
		rptr->removeCar(car2->getName());
		cout << "Removed car2 Size should be one " << rptr->getSize() << endl;
	}
	else {
		cout << car2->getName() << " Won!" << endl;
		rptr->removeCar(car1->getName());
		cout << "Removed car1 Size should be one " << rptr->getSize() << endl;
	}
	return 0;
}
