// main.cpp
#include "io_handling.h"
#include "VacuumCleaner.h"

int main() {
    // FileReader fr = FileReader("INPUT_FORMAT.txt");
    // FileReader::file_reader_output args = fr.readFile();
    // std::cout << args.max_battery_steps << std::endl;
    // std::cout << args.max_num_of_steps << std::endl;
    // args.docking_loc.print();
    // std::cout << "total dirt: " << args.house_map.calc_total_dirt() << std::endl;
    // FileWriter fw("output.txt");
    // fw.writeHouse(args.house_map);
    // return 0;

    FileReader fr("INPUT_FORMAT.txt");
    FileReader::file_reader_output args = fr.readFile();
    VacuumCleaner vacuumCleaner(args.max_num_of_steps, args.max_battery_steps, args.house_map, args.docking_loc);
    vacuumCleaner.cleanHouse();
    FileWriter fw("output.txt");
    fw.writeHouse(vacuumCleaner.getHouse());
    fw.writePath(vacuumCleaner.getPath());
}