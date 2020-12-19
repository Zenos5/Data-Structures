#include "Rocket.h"
#define SPEED_INCREASE 2
int Rocket::getSpeed() const
{
    return speed * SPEED_INCREASE;
}