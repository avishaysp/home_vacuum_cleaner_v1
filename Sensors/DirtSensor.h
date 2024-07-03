// DirtSensor.h

#pragma once
#include "house.h"

class DirtSensor {
    const House& house;
    const House::Location& curr_location;


public:
    DirtSensor(const House& house, const House::Location& curr_location);

    size_t getDirtLevel() const;
};


