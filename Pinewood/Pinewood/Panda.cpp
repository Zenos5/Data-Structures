#include "Panda.h"
#define SPEED_DECREASE 2
int Panda::getSpeed() const
{
    return speed / SPEED_DECREASE;
}