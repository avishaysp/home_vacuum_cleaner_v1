// house.h
#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>

class House {
    std::vector<std::vector<int>> mat;
    size_t rows;
    size_t cols;


    // Inner class Location
    class Location {
        size_t row;
        size_t col;

    public:
        // Constructors
        // Location();
        Location(size_t row, size_t col);

        // Getters
        size_t getRow() const;
        size_t getCol() const;

        // Setters
        void setRow(size_t x);
        void setCol(size_t y);
        void setBoth(size_t x, size_t y);

        bool operator==(const Location &other) const;
        bool operator!=(const Location &other) const;
    };

    // Inner class Location
    class Location {
        size_t row;
        size_t col;

    public:
        // Constructors
        // Location();
        Location(size_t row, size_t col);

        // Getters
        size_t getRow() const;
        size_t getCol() const;

        // Setters
        void setRow(size_t x);
        void setCol(size_t y);
        void setBoth(size_t x, size_t y);

        bool operator==(const Location &other) const;
        bool operator!=(const Location &other) const;
    };

public:
    House(size_t rows, size_t cols);

    static const std::unordered_map<char, int> passages_to_negs;
    static const std::unordered_map<int, char> negs_to_passages;

    void print() const;

    int getVal(Location loc);
    void setVal(Location loc, int value);

    int getRowsCount();
    int getColsCount();

    size_t calc_total_dirt() const;


    // Inner class Location
    class Location {
        size_t row;
        size_t col;

    public:
        // Constructors
        // Location();
        Location(size_t x, size_t y);
        Location();


        // Getters
        size_t getRow() const;
        size_t getCol() const;

        // Setters
        void setRow(size_t x);
        void setCol(size_t y);
        void setBoth(size_t x, size_t y);

        bool operator==(const Location &other) const;
        bool operator!=(const Location &other) const;

        void print() const;
    };
};
