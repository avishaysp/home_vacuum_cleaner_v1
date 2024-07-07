#pragma once

#include <random>
#include "Sensors/BatterySensor.h"
#include "Sensors/WallSensor.h"
#include "Sensors/DirtSensor.h"
#include "Path.h"

class Algorithm {
    WallSensor wallSensor;
    BatterySensor batterySensor;
    DirtSensor dirtSensor;
    size_t battery_size;
    Path current_path;
    bool isDocStation;

    std::random_device rd;
    std::mt19937 gen;

    bool isDockinStation() const;

    Direction decide() const;

    void updatePath(const Direction decition);

    Direction chooseRandomDirection(const std::vector<Direction>& vec) const;

    Direction locationsDiffToDirection(House::Location curr, House::Location next) const;

    public:
        Algorithm(const WallSensor& wallSensor, const BatterySensor& batterySensor, const DirtSensor& dirtSensor, const size_t battery_size,  const House::Location starting_location);

        Direction nextStep();


};


