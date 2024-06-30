// io_handling.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "house.h"


class FileReader {
    std::string filePath;

    std::vector<std::string> split(const std::string &str, const char delimiter) const {
        std::vector<std::string> result;
        std::stringstream ss(str);
        std::string item;

        while (std::getline(ss, item, delimiter)) {
            result.push_back(item);
        }

        return result;
    }

    size_t str_to_size_t(const std::string &str) const {
        try {
            size_t res = std::stoull(str);
            return res;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
            std::exit(EXIT_FAILURE);
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    House::Location parse_location(const std::string &str) const {
        auto tmp_vec = split(str, '|');
        return House::Location(
            str_to_size_t(tmp_vec[0].substr(1)),                            // x
            str_to_size_t(tmp_vec[1].substr(0, tmp_vec[1].size() - 1))      // y
        );
    }


    std::pair<size_t, size_t> get_house_dimensions(const std::string& filename) const {
        // opens a new fd, to avoid seek when returns
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open the file." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // remove first line with the args
        std::string first_line;
        if (!std::getline(file, first_line)) {
            std::cerr << "Error or empty file content." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::istringstream stream(content);
        std::string line;
        size_t rows = 0;
        size_t maxCols = 0;

        while (std::getline(stream, line)) {
            if (!line.empty()) {
                rows++;
                size_t cols = line.length();
                if (cols > maxCols) {
                    maxCols = cols;
                }
            }
        }

        file.close();
        return {rows, maxCols};
    }


public:
    FileReader(const std::string& filePath) : filePath(filePath) {}

    struct file_reader_output {
        size_t max_battery_steps;
        size_t max_num_of_steps;
        House::Location docking_loc;
        House house_map;
    };


    file_reader_output readFile() const {
        size_t max_battery_steps;
        size_t max_num_of_steps;
        House::Location docking_loc;

        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Failed to open the file: " << filePath << std::endl;
            std::exit(EXIT_FAILURE);
        }

        std::string first_line;
        if (std::getline(file, first_line)) {
            auto args = split(first_line, ',');
            max_battery_steps = str_to_size_t(args[0]);
            max_num_of_steps = str_to_size_t(args[1]);
            docking_loc = parse_location(args[2]);
        } else {
            std::cerr << "Failed to read first line of input file" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        auto [rows, cols] = this->get_house_dimensions(filePath);
        House house = House(rows, cols);

        std::string line;
        size_t i = 0;
        while (std::getline(file, line)) {
            size_t j = 0;
            for (char& ch : line) {
                if (isdigit(ch)) {
                    house.setVal(i, j, ch - '0');
                } else {
                    auto it = House::passages_to_negs.find(ch);
                    if (it != House::passages_to_negs.end()) {
                        house.setVal(i, j, it->second);
                    } else {
                        std::cerr << "Unexpected character '" << ch << "' at (" << i << ", " << j << ")" << std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                }
                j++;
            }
            i++;
        }
        file.close();

        return {max_battery_steps, max_num_of_steps, docking_loc, house};
    }
};
