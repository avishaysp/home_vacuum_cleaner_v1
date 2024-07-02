#pragma once
#include "house.h"

class DirtSensor {
    House::Location& location;
    House& house;

public:
    DirtSensor(House::Location& location, House& house); 
    size_t getDirt() const;
};

