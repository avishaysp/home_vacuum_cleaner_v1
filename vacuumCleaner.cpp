#include "VacuumCleaner.h"


VacuumCleaner::VacuumCleaner(size_t max_steps, size_t battery_size, House& house, House::Location docking_loc)
    : max_steps(max_steps),
      battery_size(battery_size),
      current_battery(battery_size),
      house(house),
      docking_loc(docking_loc),
      current_location(docking_loc),
      history_path(docking_loc),
      battery_sensor(current_battery),
      wall_sensor(house, current_location),  
      dirt_sensor(house, current_location),
      current_total_dirt(house.calc_total_dirt()) {}


void VacuumCleaner::cleanHouse() {
    Algorithm algo(wall_sensor, battery_sensor, dirt_sensor, battery_size, current_location);
    for (int i = 0; i < max_steps; ++i) {
        Direction step = algo.nextStep();

        //Stay in docking station
        if ((step.getValue() == Direction::Value::Stay) && (current_location == docking_loc)) {
            size_t updated_battery = current_battery + battery_size / 20;
            current_battery = (updated_battery > battery_size) ? battery_size : updated_battery;
        } 

        //Stay and clean
        else if (step.getValue() == Direction::Value::Stay) {
            set_total_dirt();
            update_house();
            current_battery -= 1;
        } 

        //Move to another location
        else {
            move(step);
            current_battery -= 1;
        }

        add_to_history();
        

    }
}

void VacuumCleaner::move(const Direction direction) {
    current_location.setBoth(current_location.getRow() + direction.getX(), current_location.getCol() + direction.getY());
}

void VacuumCleaner::add_to_history() {
    history_path.addEntry(current_location);
}

void VacuumCleaner::set_total_dirt() {
    current_total_dirt -= 1;
}

void VacuumCleaner::update_house() {
    house.getTile(current_location).removeOneDirt();
}

