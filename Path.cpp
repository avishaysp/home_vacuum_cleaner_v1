// Path.cpp

#include "Path.h"

Path::Path(House::Location start_loc) {
    vec.push_back(start_loc);
}

void Path::print() {
    for (const auto& loc : vec) {
        loc.print();
    }
}

void Path::addEntry(House::Location loc) {
    vec.push_back(loc);
}

House::Location Path::popStep() {
    if (!vec.empty()) {
        House::Location last = vec.back();
        vec.pop_back();
        return last;
    }
    std::cerr << "Popped the first elem in the Path. Big No No." << std::endl;
    std::exit(EXIT_FAILURE);
}
