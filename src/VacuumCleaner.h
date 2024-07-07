#pragma once
#include <string>
#include <iostream>
#include "Algorithm.h"
#include "house.h"
#include "Sensors/WallSensor.h"
#include "Sensors/DirtSensor.h"
#include "Sensors/BatterySensor.h"


class VacuumCleaner {
    const size_t battery_size;
    size_t current_battery;
    const size_t max_steps;
    House& house;
    const House::Location docking_loc;
    House::Location current_location;
    Path history_path;
    const WallSensor wall_sensor;
    const BatterySensor battery_sensor;
    const DirtSensor dirt_sensor;
    size_t current_total_dirt;

    void move(const Direction direction);
    void addToHistory();
    void decreaseTotalDirt();
    void updateHouse();


    public:
        VacuumCleaner(size_t max_steps, size_t battery_size, House& house, House::Location docking_loc);

        struct vacuum_cleaner_output {
            size_t battery_level;
            size_t dirt_left;
            bool is_in_doc;
        };

        vacuum_cleaner_output cleanHouse();
        const Path& getPath() const;
        size_t getHistoryLength() const;
};
