// DirtSensor.cpp

#include "DirtSensor.h"

DirtSensor::DirtSensor(const House& house, House::Location& curr_location) :  house(house), curr_location(curr_location) { }

size_t DirtSensor::getDirtLevel() const {
    return this->house.getDirt(this->curr_location);
}