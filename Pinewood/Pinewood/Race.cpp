#include "Race.h"


using namespace std;
bool Race::addCar(string info) {
    stringstream ss(info);
    string name, type;
    int speed;

    if (ss >> name >> type >> speed) {
        cout << "addCar got " << name << " " << type << " " << speed << endl;
        if (type == "R") { /* Rocket */
            cout << "Adding Rocket" << endl;
            carVec.push_back(new Rocket(name, speed));
        }
        else if (type == "P") { /* Panda */
            cout << "Adding Panda" << endl;
            carVec.push_back(new Panda(name, speed));
        }
        else {
            return false; //not a valid type of car
        }
        return true;
    }
    return false; //invalid input, not enough tokens or wrong input type
}

bool Race::removeCar(string name) {
    for (int i = 0; i < carVec.size(); i++) {
        if (carVec.at(i)->getName() == name) {
            carVec.erase(carVec.begin() + i);
            return true;
        }
    }
    return false;
}

CarInterface* Race::getCar(string name) {
    for (Car* cp : carVec) {
        if (cp->getName() == name) {
            return cp;
        }
    }
    return NULL;
}

int Race::getSize() const {
    return NULL;
}