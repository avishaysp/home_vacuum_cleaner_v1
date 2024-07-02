// io_handling.cpp
#include "io_handling.h"




std::vector<std::string> FileReader::split(const std::string &str, const char delimiter) const {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

size_t FileReader::str_to_size_t(const std::string &str) const {
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

House::Location FileReader::parse_location(const std::string &str) const {
    auto tmp_vec = split(str, '|');
    return House::Location(
        str_to_size_t(tmp_vec[0].substr(1)),                            // x
        str_to_size_t(tmp_vec[1].substr(0, tmp_vec[1].size() - 1))      // y
    );
}


std::pair<size_t, size_t> FileReader::get_house_dimensions(const std::string& filename) const {
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

void FileReader::surround_house_w_walls(House& house) const {
    size_t rows = house.getRowsCount();
    size_t cols = house.getColsCount();
    for (size_t i = 0; i < cols; i++) {
        int value = (i == 0 || i == cols - 1)? '+' : '-';
        char ch = House::passages_to_negs.find(value)->second;
        house.setVal(0, i, ch);
        house.setVal(rows - 1, i, ch);
    }
    for (size_t j = 0; j < rows; j++) {
        int value = (j == 0 || j == rows - 1)? '+' : '|';
        char ch = House::passages_to_negs.find(value)->second;
        house.setVal(j, 0, ch);
        house.setVal(j, cols - 1, ch);
    }

}

void FileReader::read_house(std::__1::ifstream &file, House &house) const {
    std::string line;
    size_t i = 1; // start from 1 for padding
    while (std::getline(file, line)) {
        size_t j = 1; // start from 1 for padding
        for (char &ch : line) {
            if (isdigit(ch)) {
                house.setVal(i, j, ch - '0');
            }
            else {
                auto it = House::passages_to_negs.find(ch);
                if (it != House::passages_to_negs.end()) {
                    house.setVal(i, j, it->second);
                }
                else {
                    std::cerr << "Unexpected character '" << ch << "' at (" << i << ", " << j << ")" << std::endl;
                    std::exit(EXIT_FAILURE);
                }
            }
            j++;
        }
        i++;
    }
}

FileReader::FileReader(const std::string& filePath) : filePath(filePath) {}


FileReader::file_reader_output FileReader::readFile() const {
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
        docking_loc.setBoth(docking_loc.getRow() + 1, docking_loc.getCol() + 1); // acount for shift due to surraunding by walls
    } else {
        std::cerr << "Failed to read first line of input file" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    auto [rows, cols] = this->get_house_dimensions(filePath);
    // added padding for surrounding the house with walls for open house case
    House house = House(rows + 2, cols + 2);
    surround_house_w_walls(house);

    read_house(file, house);
    file.close();

    return {max_battery_steps, max_num_of_steps, docking_loc, house};
}

