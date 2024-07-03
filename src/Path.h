// Path.h

#include <vector>
#include "house.h"

class Path {
public:

    Path(House::Location start_loc);

    void print();

    void addEntry(House::Location loc);
    House::Location popStep();

private:
    std::vector<House::Location> vec;

};
