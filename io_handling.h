// io_handling.h

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "house.h"

class FileReader {
    std::string filePath;

    std::vector<std::string> split(const std::string &str, const char delimiter) const;
    size_t str_to_size_t(const std::string &str) const;
    House::Location parse_location(const std::string &str) const;
    std::pair<size_t, size_t> get_house_dimensions(const std::string& filename) const;
    void surround_house_w_walls(House& house) const;
    void read_house(std::__1::ifstream &file, House &house) const;
public:
    FileReader(const std::string& filePath);

    struct file_reader_output {
        size_t max_battery_steps;
        size_t max_num_of_steps;
        House::Location docking_loc;
        House house_map;
    };

    file_reader_output readFile() const;
};