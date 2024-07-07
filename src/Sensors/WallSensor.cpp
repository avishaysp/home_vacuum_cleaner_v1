#include "WallSensor.h"

WallSensor::WallSensor(const House& house, const House::Location& curr_location) : house(house), curr_location(curr_location) {} 


std::vector<Direction> WallSensor::getPosibbleDirections() const {
    auto& tile = house.getTile(curr_location);
    std::vector<Direction> vec = std::vector<Direction>();
    if (!tile.getNorthWall()) {
        vec.push_back(Direction(Direction::Value::North));
    }

    if (!tile.getSouthWall()) {
        vec.push_back(Direction(Direction::Value::South));
    }

    if (!tile.getEastWall()) {
        vec.push_back(Direction(Direction::Value::East));
    }

    if (!tile.getWestWall()) {
        vec.push_back(Direction(Direction::Value::West));
    }

    return vec;


}