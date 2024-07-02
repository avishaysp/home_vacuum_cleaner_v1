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
int House::getVal(Location loc) {
    size_t row = loc.getRow();
    size_t col = loc.getCol();

    if (row < rows && col < cols) {
        return mat[row][col];
    }
    return -99;
}

void House::setVal(Location loc, int value) {
    size_t row = loc.getRow();
    size_t col = loc.getCol();

    if (row < rows && col < cols) {
        mat[row][col] = value;
    }
}

int House::getRowsCount() {
    return rows;
}

int House::getColsCount() {
    return cols;
}

size_t House::calc_total_dirt() const {
    size_t sum = 0;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (mat[i][j] > 0) {
                sum += mat[i][j];
            }
        }
    }
    return sum;
}

/* Location */

House::Location::Location(size_t row, size_t col) : row(row), col(col) {}
House::Location::Location() : row(0), col(0) {}


// Getters for Location
size_t House::Location::getRow() const {
    return row;
}

size_t House::Location::getCol() const {
    return col;
}

// Setters for Location
void House::Location::setRow(size_t row) {
    this->row = row;
}

void House::Location::setCol(size_t col) {
    this->col = col;
}

void House::Location::setBoth(size_t row, size_t col) {
    this->row = row;
    this->col = col;
}

// Overloaded operators for Location
bool House::Location::operator==(const House::Location &other) const {
    return (row == other.row) && (col == other.col);
}

bool House::Location::operator!=(const House::Location &other) const {
    return !(*this == other);
}

void House::Location::print() const {
    std::cout << "(" << (this->row) << "|" << (this->col) << ")" << std::endl;
}