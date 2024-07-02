#include "DirtSensor.h"

DirtSensor(House::Location& location, House& house):location(location), house(house){

}

size_t DirtSensor::getDirt() const {
    return this->house.getVal(this->location);
}
