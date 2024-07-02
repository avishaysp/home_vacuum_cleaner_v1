// DirtSensor.cpp

#include "DirtSensor.h"

DirtSensor::DirtSensor(House& house, House::Location& curr_location) : curr_location(curr_location), house(house) { }

size_t DirtSensor::getDirtLevel() const {
    return this->house.getVal(this->curr_location);
}