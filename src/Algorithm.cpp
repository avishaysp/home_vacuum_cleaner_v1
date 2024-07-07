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
    return (current_path.getLength() == 1);
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
        return locationsDiffToDirection(current_location, prev_location);
    }

     if (dirtSensor.getDirtLevel()) {
        return Direction(Direction::Value::Stay);
    }

    return possible_direction;
}

void Algorithm::updatePath(const Direction decition) {
    if (decition.getValue() != Direction::Value::Stay) {
        House::Location current_location = current_path.topStep();
        current_path.addEntry(House::Location(current_location.getRow() + decition.getX(), current_location.getCol() + decition.getY()));
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

    return curr.getRow() > next.getRow() ? Direction(Direction::Value::South) : Direction(Direction::Value::North);
}
    