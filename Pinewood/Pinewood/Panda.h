#pragma once
#include "Car.h"

class Panda : public Car {
public:
    Panda(string pandaname, int pandaspeed) :Car(pandaname, pandaspeed) {};
    ~Panda() {};
    int getSpeed() const;
};