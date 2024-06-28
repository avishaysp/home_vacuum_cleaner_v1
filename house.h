// house.h
#pragma once

#include <cstddef>
#include <vector>
#include <iostream>

class House {
    std::vector<std::vector<int>> mat;

public:
    House(size_t rows, size_t cols);

    void print() const;

    int getVal(size_t row, size_t col);
    void setVal(size_t row, size_t col, int value);

    int getRowsCount();
    int getColsCount();

    enum PASSAGES {
        OPEN = ' ',
        CORNER = '+',
        VERTICAL_WALL = '-',
        HORIZONTAL_WALL = '|'
    };

    // Inner class Location
    class Location {
        size_t x;
        size_t y;

    public:
        // Constructors
        // Location();
        Location(size_t x, size_t y);

        // Getters
        size_t getX() const;
        size_t getY() const;

        // Setters
        void setX(size_t x);
        void setY(size_t y);
        void setBoth(size_t x, size_t y);

        bool operator==(const Location &other) const;
        bool operator!=(const Location &other) const;
    };
};
