#pragma once
#include "Car.h"

class Rocket :public Car {
public:
    Rocket(string pandaname, int pandaspeed) :Car(pandaname, pandaspeed) {};
    ~Rocket() {};
    int getSpeed() const;
};