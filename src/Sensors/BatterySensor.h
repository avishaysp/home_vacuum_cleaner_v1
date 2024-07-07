// BatterySensor.h
#pragma once

#include <vector> // for size_t

class BatterySensor {
    size_t& battery;


public:
    BatterySensor(size_t& battery);
    size_t getBattery() const;
};
