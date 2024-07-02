#include "BatterySensor.h"

BatterySensor::BatterySensor(size_t& battery) : battery(battery) {}

size_t BatterySensor::getBattery() const {
    return battery;
}

