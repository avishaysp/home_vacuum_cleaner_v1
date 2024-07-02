#pragma once

#include <vector>

class WallSensor {
public:
    enum class Direction {
        North,
        South,
        East,
        West
    };

    WallSensor(const std::vector<Direction>& newDirections); 

    std::vector<Direction> getDirections() const;
    void setDirections(const std::vector<Direction>& newDirections);

private:
    std::vector<Direction> directions; 

};
