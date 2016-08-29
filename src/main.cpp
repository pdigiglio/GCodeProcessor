/// \file

#include "GCodeProcessor.h"

#include <iostream>
#include <string>

int main (int argc, char *argv[]) {
    // Check the file name is given
    if (argc != 2) {
        std::cerr << "Wrong number of arguments" << std::endl;
        std::abort();
    } 

    // Read the file in
    GCodeProcessor gcode_processor(static_cast<std::string>(argv[1]));
    // Process the file
    gcode_processor.process();
    // Print the processed file to std::cout
//    gcode_processor.print();

    return 0;
}
