#include "Algorithm.h"
#include "house.h"

Algorithm::Algorithm(const WallSensor& wallSensor, const BatterySensor& batterySensor, const DirtSensor& dirtSensor, const size_t battery_size, const House::Location starting_location)
    : wallSensor(wallSensor),
      batterySensor(batterySensor),
      dirtSensor(dirtSensor),
      battery_size(battery_size),
      current_path(starting_location),
      gen(rd())
     {}

Direction Algorithm::nextStep() {
    Direction decition = decide();
    updatePath(decition);
    return decition;
}

bool Algorithm::isDockinStation() const{
    return (current_path.getLocation(0) == current_path.topStep());
}

Direction Algorithm::decide() const {
    size_t battery = batterySensor.getBattery();
    std::vector<Direction> possible_directions = wallSensor.getPosibbleDirections();
    for (const auto& direction : possible_directions) {
        std::cout << direction.toString() << std::endl;
    }
    std::cout << "Dirt " << dirtSensor.getDirtLevel() << " for loc " << current_path.topStep().toString() << std::endl;
    Direction possible_direction = possible_directions.size() ? chooseRandomDirection(possible_directions) : Direction(Direction::Value::Stay);

    if (isDockinStation() && battery < battery_size) {
        std::cout << "decide to Stay because charging" << std::endl;
        return Direction(Direction::Value::Stay);
    }

    if (isDockinStation()) {
        std::cout << "decide " << possible_direction.toString() << " in docking station " << std::endl;
        return possible_direction;
    }


    if (current_path.getLength() >= battery - 1) {
        House::Location current_location = current_path.topStep();
        House::Location prev_location = current_path.getPrev();
        possible_direction = locationsDiffToDirection(current_location, prev_location);
        std::cout << "decide " << possible_direction.toString() << " to return to docking station " << std::endl;
        return possible_direction;
    }

     if (dirtSensor.getDirtLevel()) {
        std::cout << "decide to Stay because cleaning" << std::endl;
        return Direction(Direction::Value::Stay);
    }

    std::cout << "decide " << possible_direction.toString() << " to move " << std::endl;
    return possible_direction;
}

void Algorithm::updatePath(const Direction decition) {
    current_path.print();
    if (decition.getValue() != Direction::Value::Stay) {
        House::Location prev_location = current_path.topStep();
        House::Location current_location = House::Location(prev_location.getRow() + decition.getX(), prev_location.getCol() + decition.getY());
        std::cout << "prev_location: " << prev_location.toString() << ", current_location: " << current_location.toString() << std::endl;
        int idx = current_path.getIndexOfLocation(current_location);
        if (idx != -1) {
            current_path.cutPath(idx);
        } else {
            current_path.addEntry(current_location);
        }
    }
    return;
}

Direction Algorithm::chooseRandomDirection(const std::vector<Direction>& vec) const {
    std::uniform_int_distribution<> dis(0, static_cast<int>(vec.size()) - 1);
    size_t randoIndex = dis(gen);
    return vec[randoIndex];
}

Direction Algorithm::locationsDiffToDirection(const House::Location curr, const House::Location next) const {

    if (curr.getRow() == next.getRow()) {
        return curr.getCol() > next.getCol() ? Direction(Direction::Value::West) : Direction(Direction::Value::East);
    }

    return curr.getRow() > next.getRow() ? Direction(Direction::Value::North) : Direction(Direction::Value::South);
}
