///    @file  CommandLineArguments.cpp
///    @date  09/12/16
///  @author  Paolo Di Giglio (github.com/pdigiglio),
///           <p.digiglio91@gmail.com>

#include "CommandLineArguments.h"
#include "TriggerParameters.h"

#include <stdexcept>
#include <string>

std::string parseFileName(int argc, const char *argv[]) {
    for (int i = 1; i < argc; ++i)
        if (std::string(argv[i]) == "--file")
            return std::string(argv[i+1]);
    
    throw std::invalid_argument("Can't parse file name.");
}

double parseAngle(int argc, const char *argv[]) {
    for (int i = 1; i < argc; ++i)
        if (std::string(argv[i]) == "--angle")
            return std::stod(std::string(argv[i+1]));
    
    throw std::invalid_argument("Can't parse --angle value.");
}

double parseLength(int argc, const char *argv[]) {
    for (int i = 1; i < argc; ++i)
        if (std::string(argv[i]) == "--length")
            return std::stod(std::string(argv[i+1]));
    
    throw std::invalid_argument("Can't parse --length value.");
}

CommandLineArguments::CommandLineArguments(int argc, const char *argv[]) :
    FileName_(std::move(parseFileName(argc, argv))),
    TriggerParameters_(parseLength(argc, argv), parseAngle(argc, argv))
{
    if (argc != 7)
        throw std::invalid_argument("Wrong number of parameters.");
}
