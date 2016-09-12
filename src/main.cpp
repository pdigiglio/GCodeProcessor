/// \file

#include "CommandLineArguments.h"
#include "GCodeProcessor.h"
#include "TriggerParameters.h"

#include <exception>
#include <iostream>
#include <string>

int main (int argc, const char *argv[]) {
    // parse command line options
    try {
        CommandLineArguments cmdArgs(argc, argv);
        // Read the file in
        GCodeProcessor gcode_processor(cmdArgs.fileName(),
                TriggerParameters(cmdArgs.length(), cmdArgs.angle()));
        // Process the file
        gcode_processor.process();
        // Print the processed file to std::cout
        //    gcode_processor.print();
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


    return 0;
}
