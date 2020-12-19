#ifndef RACE_H_
#define RACE_H_
#include "RaceInterface.h"
#include "CarInterface.h"
#include "Car.h"
#include "Rocket.h"
#include "Panda.h"
#include <vector>
#include <sstream>

class Race : public RaceInterface {
private:
	vector<Car*> carVec;

public:
	Race() {}
	~Race() {}

	bool addCar(string info);

	bool removeCar(string name);

	CarInterface* getCar(string name);

	int getSize() const;
};
#endif