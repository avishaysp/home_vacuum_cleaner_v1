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

    static const std::unordered_map<char, int> passages_to_negs;
    static const std::unordered_map<int, char> negs_to_passages;

    class Location {
        size_t row;
        size_t col;

    public:
        // Constructors
        Location();
        Location(size_t row, size_t col);

        // Getters
        size_t getRow() const;
        size_t getCol() const;

        // Setters
        void setRow(size_t row);
        void setCol(size_t col);
        void setBoth(size_t row, size_t col);

        bool operator==(const Location& other) const;
        bool operator!=(const Location& other) const;

        void print() const;
    };

    void print() const;

    int getVal(Location loc) const;
    int getVal(size_t row, size_t col) const;
    void setVal(Location loc, int value);
    void setVal(size_t row, size_t col, int value);

    void removeOneDirt(const Location& loc);

    int getRowsCount();
    int getColsCount();

    size_t calc_total_dirt() const;
};
