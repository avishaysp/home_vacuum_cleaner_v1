#include "BatterySensor.h"

BatterySensor::BatterySensor(int& battery) : battery(battery) {} // Initialize battery to 100 in the constructor

int BatterySensor::getBattery() const {
    return battery;
}
 
