#pragma once

#include <vector>
#include "utils/Direction.h"
#include "house.h"

class WallSensor {
    const House& house;
    const House::Location& curr_location;

public:

    WallSensor(const House& house, const House::Location& curr_location);

    std::vector<Direction> getPosibbleDirections() const;
};
