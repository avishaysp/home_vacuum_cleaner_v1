// DirtSensor.cpp

#include "DirtSensor.h"

DirtSensor::DirtSensor(const House& house, const House::Location& curr_location) : curr_location(curr_location), house(house) { }

size_t DirtSensor::getDirtLevel() const {
    return this->house.getDirt(this->curr_location);
}