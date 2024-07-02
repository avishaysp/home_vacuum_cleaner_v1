// DirtSensor.h

#pragma once
#include "house.h"

class DirtSensor {
    House& house;
    House::Location& curr_location;


public:
    DirtSensor(House& house, House::Location& curr_location);

    size_t getDirtLevel() const;
};


