#include "house.h"

/* House */

House::House(std::vector<std::vector<int>> &mat) : mat(mat) {}

House::House(size_t rows, size_t cols) : mat(rows, std::vector<int>(cols)) {}


void House::print() const {
    for (const auto& row : mat) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

int House::getVal(size_t row, size_t col) {
    if (row >= 0 && row < mat.size() && col >= 0 && col < mat[0].size()) {
        return mat[row][col];
    }
    return -99;
}

void House::setVal(size_t row, size_t col, int value) {
    if (row >= 0 && row < mat.size() && col >= 0 && col < mat[0].size()) {
        mat[row][col] = value;
    }
}

int House::getRowsCount() {
    return mat.size();
}

int House::getColsCount() {
    return mat[0].size();
}

/* Location */

House::Location::Location(size_t x, size_t y) : x(x), y(y) {}
// House::Location::Location() : x(0), y(0) {}


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
