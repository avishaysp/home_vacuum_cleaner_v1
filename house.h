// house.h
#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>

class House {
    std::vector<std::vector<int>> mat;
    size_t rows;
    size_t cols;


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
        HORIZONTAL_WALL = '|',
    };

    static const std::unordered_map<char, int> passages_to_negs;
    static const std::unordered_map<int, char> negs_to_passages;

    // Inner class Location
    class Location {
        size_t x;
        size_t y;

    public:
        // Constructors
        // Location();
        Location(size_t x, size_t y);
        Location();


        // Getters
        size_t getX() const;
        size_t getY() const;

        // Setters
        void setX(size_t x);
        void setY(size_t y);
        void setBoth(size_t x, size_t y);

        bool operator==(const Location &other) const;
        bool operator!=(const Location &other) const;

        void print() const;
    };
};
