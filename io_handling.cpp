// io_handling.cpp
#include "io_handling.h"

StepHouse::StepHouse(std::__1::ifstream &file) {
    std::string line;
    rows = 0;
    max_col = 0;
    while (std::getline(file, line)) {
        size_t cur_col = line.size();
        max_col = cur_col > max_col ? cur_col : max_col;
        this->mat.emplace_back(line.begin(), line.end());
        rows++;
    }
}

std::pair<size_t, size_t> StepHouse::getFirstTileIndecies() const {
    if (isdigit(mat[0][0]) || mat[0][0] == '/') {
        return {0, 0};

    } else if (isdigit(mat[0][1]) || mat[0][1] == '/') {
        return {0, 1};

    } else if (isdigit(mat[1][0]) || mat[1][0] == '/') {
        return {1, 0};
    }
    return {1, 1};
}

void StepHouse::print() const {
    for (const auto& row : mat) {
        for (char ch : row) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
}

std::vector<std::string> FileReader::split(const std::string &str, const char delimiter) const {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

size_t FileReader::strToSize_t(const std::string &str) const {
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

House::Location FileReader::parseLocation(const std::string &str) const {
    auto tmp_vec = split(str, '|');
    return House::Location(
        strToSize_t(tmp_vec[0].substr(1)),                            // x
        strToSize_t(tmp_vec[1].substr(0, tmp_vec[1].size() - 1))      // y
    );
}

std::pair<size_t, size_t> FileReader::getHouseDimensions(const std::string& filename) {
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

void FileReader::surroundHouseWithWalls(const StepHouse& step_house, House &house) const {
    auto [first_step_i, first_step_j] = step_house.getFirstTileIndecies();
    if (first_step_j == 0) {
        for (size_t house_i = 0; house_i < house.getRowsCount(); house_i++) {
            house.getTile(house_i, 0).setWestWall(true);
        }
    }
    if (first_step_i == 0) {
        for (size_t house_j = 0; house_j < house.getColsCount(); house_j++) {
            house.getTile(0, house_j).setNorthWall(true);
        }
    }

    // TODO: Go line by line and row by row and add walls acording to '/'s
}

void FileReader::parseHouse(const StepHouse& step_house, House &house) const {
    auto [first_step_i, first_step_j] = step_house.getFirstTileIndecies();

    // read only dirt values

    size_t house_i = 0;
    size_t house_j = 0;
    for (size_t step_i = first_step_i; step_i < step_house.mat.size(); step_i += 2) {
        for (size_t step_j = first_step_j; step_j < step_house.mat[step_i].size(); step_j += 2) {

            House::Tile& tile = house.getTile(house_i, house_j);
            char val = step_house.mat[step_i][step_j];

            if (isdigit(val)) {
                tile.setDirt(val);
            }
            house_j++;
        }
        house_i++;
    }

    // add walls from step_house
    house_i = 0;
    house_j = 0;
    for (size_t step_i = first_step_i; step_i < step_house.mat.size(); step_i += 2) {
        for (size_t step_j = first_step_j; step_j < step_house.mat[step_i].size(); step_j += 2) {

            House::Tile& tile = house.getTile(house_i, house_j);

            if (0 < step_i) {
                char north = step_house.mat[step_i - 1][step_j];
                if (north == '-') {
                    tile.setNorthWall(true);
                }
            }
            if (step_i < step_house.rows - 1) {
                char south = step_house.mat[step_i + 1][step_j];
                if (south == '-') {
                    tile.setSouthWall(true);
                }
            }
            if (0 < step_j) {
                char west = step_house.mat[step_i][step_j - 1];
                if (west == '-') {
                    tile.setWestWall(true);
                }
            }
            if (step_j < step_house.mat[step_i].size() - 1) {
                char north = step_house.mat[step_i - 1][step_j];
                if (north == '-') {
                    tile.setNorthWall(true);
                }
            }

            house_j++;
        }
        house_i++;
    }
}

FileReader::FileReader(const std::string& file_path) : file_path(file_path) {}


FileReader::file_reader_output FileReader::readFile() const {
    size_t max_battery_steps;
    size_t max_num_of_steps;
    House::Location docking_loc;

    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << file_path << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string first_line;
    if (std::getline(file, first_line)) {
        auto args = split(first_line, ',');
        max_battery_steps = strToSize_t(args[0]);
        max_num_of_steps = strToSize_t(args[1]);
        docking_loc = parseLocation(args[2]);
    } else {
        std::cerr << "Failed to read first line of input file" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    auto [rows, cols] = getHouseDimensions(file_path);
    StepHouse step_house(file);
    House house = House(rows, cols);
    parseHouse(step_house, house);
    surroundHouseWithWalls(step_house, house);
    file.close();

    return {max_battery_steps, max_num_of_steps, docking_loc, house};
}

FileWriter::FileWriter(const std::string& file_path) : file_path(file_path) {}

void FileWriter::writeHouse(const House& house) {
    std::ofstream file(file_path, std::ios_base::app);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }

    size_t rows = house.getRowsCount();
    size_t cols = house.getColsCount();

    for (size_t row = 0; row < rows; ++row) {
        FileWriter::print_top_wall(file, house, row, cols);
        FileWriter::print_middle(file, house, row, cols);
    }

    // Print the bottom wall segment of the last row
    print_bottom_wall(file, house, rows - 1, cols);

    file.close();
}

void FileWriter::writePath(const Path& path) {
    std::ofstream file(file_path, std::ios_base::app);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }

    for (size_t i = 0; i < path.getLength() - 1; i++) {
        file << '<' << path.getLocation(i).getRow() << ',' << path.getLocation(i).getCol() << '> --> ';
    }
    file << '<' << path.getLocation(path.getLength() - 1).getRow() << ',' << path.getLocation(path.getLength() - 1).getCol() << '>';

    file << std::endl;

    file.close();
}

void FileWriter::print_top_wall(std::ofstream& file, const House& house, size_t row, size_t cols) const {
    file << "+";
    for (size_t col = 0; col < cols; ++col) {
        file << (house.getTile(row, col).getNorthWall() ? "-+" : " +");
    }
    file << std::endl;
}

void FileWriter::print_middle(std::ofstream& file, const House& house, size_t row, size_t cols) const {
    for (size_t col = 0; col < cols; ++col) {
        const auto& tile = house.getTile(row, col);
        file << (tile.getWestWall() ? "|" : " ") << tile.getDirt();
    }
    file << (house.getTile(row, cols - 1).getEastWall() ? "|" : " ") << std::endl;
}

void FileWriter::print_bottom_wall(std::ofstream& file, const House& house, size_t row, size_t cols) const {
    file << "+";
    for (size_t col = 0; col < cols; ++col) {
        file << (house.getTile(row, col).getSouthWall() ? "-+" : " +");
    }
    file << std::endl;
}


