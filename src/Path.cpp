// Path.cpp

#include "Path.h"

Path::Path(const House::Location start_loc) {
    vec.push_back(start_loc);
}


void Path::addEntry(const House::Location loc) {
    vec.push_back(loc);
}

size_t Path::getLength() const{
    return vec.size();
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

House::Location Path::topStep() const {
    if (!vec.empty()) {
        return vec.back();
    }
    std::cerr << "Popped the first elem in the Path. Big No No." << std::endl;
    std::exit(EXIT_FAILURE);
}

void Path::cutPath(const size_t idx){
    vec = std::vector<House::Location>(vec.begin(), vec.begin() + idx);
}

House::Location Path::getPrev() const {
    return vec.end()[-2];
}

House::Location Path::getLocation(const int idx) const {
    return vec[idx];
}





