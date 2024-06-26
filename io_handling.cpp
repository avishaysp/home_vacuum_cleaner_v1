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

public:
    FileReader(const std::string& filePath) : filePath(filePath) {}

    struct file_reader_output {
        size_t max_battery_steps;
        size_t max_num_of_steps;
        House::Location docking_loc;
        House house_map;
    };


    const file_reader_output readFile() const {
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Failed to open the file: " << filePath << std::endl;
            return;
        }

        std::string line;
        if (std::getline(file, line)) {
            auto args = split(line, ',');

            size_t max_battery_steps = str_to_size_t(args[0]);
            size_t max_num_of_steps = str_to_size_t(args[0]);
        }

        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }

        file.close();
    }
};
