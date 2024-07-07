#include "VacuumCleaner.h"


VacuumCleaner::VacuumCleaner(size_t max_steps, size_t battery_size, House& house, House::Location docking_loc)
    : battery_size(battery_size),
      current_battery(battery_size),
      max_steps(max_steps),
      house(house),
      docking_loc(docking_loc),
      current_location(docking_loc),
      history_path(docking_loc),
      wall_sensor(house, current_location),
      battery_sensor(current_battery),
      dirt_sensor(house, current_location),
      current_total_dirt(house.calc_total_dirt()) {}


void VacuumCleaner::cleanHouse() {
    Algorithm algo(wall_sensor, battery_sensor, dirt_sensor, battery_size, current_location);
    for (size_t i = 0; i < max_steps; ++i) {
        if (current_total_dirt <= 0) {
            break;
        }
        Direction step = algo.nextStep();

        //Stay in docking station
        if ((step.getValue() == Direction::Value::Stay) && (current_location == docking_loc)) {
            size_t updated_battery = current_battery + battery_size / 20;
            current_battery = (updated_battery > battery_size) ? battery_size : updated_battery;
        }

        //Stay and clean
        else if (step.getValue() == Direction::Value::Stay) {
            decreaseTotalDirt();
            updateHouse();
            current_battery -= 1;
        }

        //Move to another location
        else {
            move(step);
            current_battery -= 1;
        }

        addToHistory();
    }
}


const Path& VacuumCleaner::getPath() const {
    return history_path;
}


void VacuumCleaner::move(const Direction direction) {
    current_location.setBoth(current_location.getRow() + direction.getX(), current_location.getCol() + direction.getY());
}

void VacuumCleaner::addToHistory() {
    history_path.addEntry(current_location);
}

void VacuumCleaner::decreaseTotalDirt() {
    current_total_dirt -= 1;
}

void VacuumCleaner::updateHouse() {
    house.getTile(current_location).removeOneDirt();
}

size_t VacuumCleaner::getHistoryLength() const {
    return history_path.getLength();
}