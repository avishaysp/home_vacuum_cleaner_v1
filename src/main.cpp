// main.cpp
#include "io_handling.h"
#include "VacuumCleaner.h"

int main() {
    FileReader fr("INPUT_FORMAT2.txt");
    FileReader::file_reader_output args = fr.readFile();
    FileWriter m("input_mat.txt");
    m.writeHouse(args.house_map);
    VacuumCleaner vacuumCleaner(args.max_num_of_steps, args.max_battery_steps, args.house_map, args.docking_loc);

    vacuumCleaner.cleanHouse();
    FileWriter fw("output.txt");
    fw.writeHouse(vacuumCleaner.getHouse());
    fw.writePath(vacuumCleaner.getPath());
    return 0;
}