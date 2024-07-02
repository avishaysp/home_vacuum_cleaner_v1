#include "WallSensor.h"

WallSensor::WallSensor(const std::vector<Direction>& newDirections) : directions{newDirections} {} // Initialize directions to an empty vector

std::vector<WallSensor::Direction> WallSensor::getDirections() const {
    return directions;
}

void WallSensor::setDirections(const std::vector<Direction>& newDirections) {
    directions = newDirections;
}
