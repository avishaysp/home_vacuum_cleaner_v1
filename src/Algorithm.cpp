#include "Algorithm.h"
#include "house.h"

Algorithm::Algorithm(const WallSensor& wallSensor, const BatterySensor& batterySensor, const DirtSensor& dirtSensor, const size_t battery_size, const House::Location starting_location)
    : wallSensor(wallSensor),
      batterySensor(batterySensor),
      dirtSensor(dirtSensor),
      battery_size(battery_size),
      current_path(starting_location),
      gen(rd()) {}

Direction Algorithm::nextStep() {
    Direction decition = decide();
    if (!isDecitionPossible(decition)) {
        std::cerr << "Made an impossible decition. Exiting" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    updatePath(decition);
    return decition;
}

bool Algorithm::isDockinStation() const {
    return (current_path.getLocation(0) == current_path.topStep());
}

Direction Algorithm::decide() const {
    size_t battery = batterySensor.getBattery();
    std::vector<Direction> possible_directions = wallSensor.getPosibbleDirections();
    Direction possible_direction = possible_directions.size() ? chooseRandomDirection(possible_directions) : Direction(Direction::Value::Stay);

    if (isDockinStation() && battery < battery_size) {
        return Direction(Direction::Value::Stay);
    }

    if (isDockinStation()) {
        return possible_direction;
    }


    if (current_path.getLength() >= battery - 1) {
        House::Location current_location = current_path.topStep();
        House::Location prev_location = current_path.getPrev();
        possible_direction = locationsDiffToDirection(current_location, prev_location);
        return possible_direction;
    }

     if (dirtSensor.getDirtLevel()) {
        return Direction(Direction::Value::Stay);
    }

    return possible_direction;
}

void Algorithm::updatePath(const Direction decition) {
    if (decition != Direction::Value::Stay) {
        House::Location prev_location = current_path.topStep();
        House::Location current_location = House::Location(prev_location.getRow() + decition.getX(), prev_location.getCol() + decition.getY());
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

bool Algorithm::isDecitionPossible(Direction decition) const {
    auto curr_loc = current_path.topStep();
    if (curr_loc.getCol() == 0 && decition == Direction::Value::West) {
        return false;
    }
    if (curr_loc.getRow() == 0 && decition == Direction::Value::North) {
        return false;
    }
    auto pos_dir = wallSensor.getPosibbleDirections();
    if (decition == Direction::Value::Stay) {
        return true;
    }
    bool result = false;
    for (auto elem : pos_dir) {
        if (decition == elem) {
            result = true;
            break;
        }
    }
    return result;
}
