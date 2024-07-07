// io_handling.h

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "house.h"
#include "Path.h"


class FileReader {
    std::string file_path;

    class StepHouse {

    public:
        std::vector<std::vector<char>> mat;
        size_t rows;
        size_t max_col;

        StepHouse(std::__1::ifstream &file);
        std::pair<size_t, size_t> getFirstTileIndecies() const;
        void print() const;
    };

    std::vector<std::string> split(const std::string &str, const char delimiter) const;
    size_t strToSize_t(const std::string &str) const;
    House::Location parseLocation(const std::string& str) const;
    static std::pair<size_t, size_t> getHouseDimensions(const std::string& filename);
    void surroundHouseWithWalls(const StepHouse& step_house, House& house) const;
    void parseHouse(const StepHouse& step_house, House& house) const;
    bool isTransition(const StepHouse& step_house, size_t i1, size_t j1, size_t i2, size_t j2) const;

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
    void printTopWall(std::ofstream& file, const House& house, size_t row, size_t cols) const;
    void printDirt(std::ofstream& file, const House& house, size_t row, size_t cols) const;
    void printBottomWall(std::ofstream& file, const House& house, size_t row, size_t cols) const;

public:
    FileWriter(const std::string& file_path);

    void writeHouse(const House& house);

    void writePath(const Path& path);

};
