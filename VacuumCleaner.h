#pragma once
#include "House.h"
#include "Path.h"


class VacuumCleaner {
    int batterySize;
    const int maxSteps;
    House house;
    House::Location currentLocation;
    Path historyPath;
    WallSensor wallSensor;
    BatterySensor BatterySensor;
    DirtSensor DirtSensor;

    public:
        VacuumCleaner(const int maxSteps, int batterySize, House& house);

        void cleanHouse();
};
