// main.cpp
#include "io_handling.cpp"

int main() {
    FileReader fr = FileReader("INPUT_FORMAT.txt");
    FileReader::file_reader_output args = fr.readFile();
    std::cout << args.max_battery_steps << std::endl;
    std::cout << args.max_num_of_steps << std::endl;
    args.docking_loc.print();
    args.house_map.print();
    return 0;
}