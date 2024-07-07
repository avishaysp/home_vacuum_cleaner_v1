// Path.h
#pragma once

#include <vector>
#include "house.h"

class Path {
public:

    Path(House::Location start_loc);

    void print();

    void addEntry(House::Location loc);
    House::Location popStep();

    size_t getLength() const;

    void cutPath(const size_t idx);

    House::Location topStep() const;

    House::Location getPrev() const;

    House::Location getLocation(const int idx) const;

private:

    std::vector<House::Location> vec;

};
