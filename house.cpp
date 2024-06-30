// house.cpp
#include "house.h"

/* House */

House::House(size_t rows, size_t cols) : mat(rows, std::vector<int>(cols, 0)), rows(rows), cols(cols) {
    std::cout << "Creating a house with " << rows << " rows and " << cols << " colums" << std::endl;
}

const std::unordered_map<char, int> House::passages_to_negs = {
    {' ', -1},
    {'+', -2},
    {'-', -3},
    {'|', -4},
};

const std::unordered_map<int, char> House::negs_to_passages = {
    {-1, ' '},
    {-2, '+'},
    {-3, '-'},
    {-4, '|'},
};

void House::print() const {
    for (const auto& row : mat) {
        for (const auto& elem : row) {
            if (elem >= 0) {
                std::cout << elem;
            } else {
                std::cout << negs_to_passages.find(elem)->second;
            }
        }
        std::cout << std::endl;
    }
}
int House::getVal(size_t row, size_t col) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return mat[row][col];
    }
    return -99;
}

void House::setVal(size_t row, size_t col, int value) {
    // std::cout << "called setVal with row: " << row << " col: " << col << " value: " << value << std::endl;
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        mat[row][col] = value;
    } else {
        std::cout << "called setVal with row: " << row << " col: " << col << " value: " << value << std::endl;
    }
}

int House::getRowsCount() {
    return rows;
}

int House::getColsCount() {
    return cols;
}

/* Location */

House::Location::Location(size_t x, size_t y) : x(x), y(y) {}
House::Location::Location() : x(0), y(0) {}


// Getters for Location
size_t House::Location::getX() const {
    return x;
}

size_t House::Location::getY() const {
    return y;
}

// Setters for Location
void House::Location::setX(size_t x) {
    this->x = x;
}

void House::Location::setY(size_t y) {
    this->y = y;
}

void House::Location::setBoth(size_t x, size_t y) {
    this->x = x;
    this->y = y;
}

// Overloaded operators for Location
bool House::Location::operator==(const House::Location &other) const {
    return (x == other.x) && (y == other.y);
}

bool House::Location::operator!=(const House::Location &other) const {
    return !(*this == other);
}

void House::Location::print() const {
    std::cout << "(" << (this->x) << "|" << (this->y) << ")" << std::endl;
}