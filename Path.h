#include <vector>
#include "house.h"

class Path {
    enum DIRECTIONS {
        NORTH = 'north',
        SOUTH = 'south',
        EAST = 'east',
        WEST = 'west'
    };


    struct entry {
        House::Location location;
        DIRECTIONS direction;
    };

    private: 
        std::vector<entry> path;

    public:
        Path();

        void print();

        void addEntry(House::Location loc, DIRECTIONS dir);
        entry removeEntry();
        
};
