/// \file

#include "CommandLineArguments.h"
#include "GCodeProcessor.h"
#include "TriggerParameters.h"

#include <exception>
#include <iostream>
#include <string>

int main (int argc, const char *argv[]) {
    // Empty command line arguments in the main scope
    CommandLineArguments cmd;

    // parse command line options
    try {
        CommandLineArguments cmdArgs(argc, argv);
        cmd = std::move(cmdArgs);
    } catch (std::exception& e) {
        std::cerr << std::endl;

        std::cerr << e.what() << std::endl;
        std::cerr << std::endl;

        std::cerr
            << "Usage:" << std::endl
            << argv[0] << " --file <file> --angle <angle> --length <length>" << std::endl;
        std::cerr << std::endl;

        std::cerr
            << "Where:" << std::endl
            << "  <file>    The name of the file to process." << std::endl
            << "  <angle>   The minimum angle value to trigger inserition of line (in degrees)." << std::endl 
            << "  <length>  The minimum extruder travel distance to trigger inserition of line (in millimeters)." << std::endl; 
        std::cerr << std::endl;

        std::abort();
    }


    // Read the file in
    GCodeProcessor gcode_processor(std::move(cmd));
    // Process the file
    gcode_processor.process();
    // Print the processed file to std::cout
    //    gcode_processor.print();

    return 0;
}
