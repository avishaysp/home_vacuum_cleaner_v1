// io_handling.h

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "house.h"

class StepHouse {

public:

    std::vector<std::vector<char>> mat;
    size_t rows;
    size_t max_col;

    StepHouse(std::__1::ifstream &file);
    std::pair<size_t, size_t> getFirstTileIndecies() const;
    void print() const;
};

class FileReader {
    std::string file_path;


    std::vector<std::string> split(const std::string &str, const char delimiter) const;
    size_t strToSize_t(const std::string &str) const;
    House::Location parseLocation(const std::string& str) const;
    static std::pair<size_t, size_t> getHouseDimensions(const std::string& filename);
    void surroundHouseWithWalls(const StepHouse& step_house, House& house) const;
    void parseHouse(const StepHouse& step_house, House& house) const;
public:
    FileReader(const std::string& file_path);

    struct file_reader_output {
        size_t max_battery_steps;
        size_t max_num_of_steps;
        House::Location docking_loc;
        House house_map;
    };

    file_reader_output readFile() const;
};

class FileWriter {
    std::string file_path;
    void print_top_wall(std::ofstream& file, const House& house, size_t row, size_t cols) const;
    void print_middle(std::ofstream& file, const House& house, size_t row, size_t cols) const;
    void print_bottom_wall(std::ofstream& file, const House& house, size_t row, size_t cols) const;

public:
    FileWriter(const std::string& file_path);

    void writeHouse(const House& house);

};
