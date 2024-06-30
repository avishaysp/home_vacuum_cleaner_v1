// main.cpp
#include "io_handling.h"

int main() {
    FileReader fr = FileReader("INPUT_FORMAT.txt");
    FileReader::file_reader_output args = fr.readFile();
    std::cout << args.max_battery_steps << std::endl;
    std::cout << args.max_num_of_steps << std::endl;
    args.docking_loc.print();
    args.house_map.print();
    std::cout << "total dirt: " << args.house_map.calc_total_dirt() << std::endl;
    return 0;
}