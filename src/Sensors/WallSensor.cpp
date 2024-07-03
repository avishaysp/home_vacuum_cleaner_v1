#include "WallSensor.h"

WallSensor::WallSensor(const House& house, const House::Location& curr_location) : house(house), curr_location(curr_location) {} // Initialize directions to an empty vector

std::vector<Direction> WallSensor::getPosibbleDirections() const {

    std::vector<Direction> directions;
    if (house.getDirt(curr_location.getRow(), curr_location.getRow()))
}


bool WallSensor::canMove(House::Location& curr_location, Direction direction) {
    return
}