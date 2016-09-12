/// \file


#include "GCodeProcessor.h"

#include "CommandLineArguments.h"
#include "GCodeLineEntry.h"
#include "GCodeLineEntryStack.h"
#include "InputFileIterator.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

GCodeProcessor::GCodeProcessor(CommandLineArguments&& cmd_line_args) :
    InputEntriesStack_(std::make_unique<GCodeLineEntryStack>(3,
                std::forward<CommandLineArguments>(cmd_line_args).triggerParameters()))
{
    std::ifstream inFile(std::forward<CommandLineArguments>(cmd_line_args).fileName(), std::ios::in);
    std::copy(InputFileIterator(inFile), InputFileIterator::end(),
            std::inserter(InputFileLines_, InputFileLines_.begin()));
}

// Helper function to split a string and put the separate substrings
// into a vector<std::string>
inline decltype(auto) split_string(const std::string& input_string) {
    std::istringstream iss(input_string);
    return std::vector<std::string>{
        std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>()};
}

// Helper function to create a GCodeLineEntry out of the vector
// of line items found in the .gcode input file (i.e. G1, X1.123 and so on)
decltype(auto) interpret_entry (const std::vector<std::string>& input) {
    // empty line entry
    GCodeLineEntry line_entry;
    bool entry_is_valid = false;

    if (input.size() > 3) {
        std::string::size_type n;
        if (input[0].find('G') == 0) {
            line_entry.G = std::stoi(input[0].substr(1));

            if (input[1].find('X') == 0) {
                line_entry.X = std::stod(input[1].substr(1));

                if (input[2].find('Y') == 0) {
                    line_entry.Y = std::stod(input[2].substr(1));

                    if (input[3].find('E') == 0) {
                        line_entry.E = std::stod(input[3].substr(1));
                        entry_is_valid = true;
                    }
                }
            }
        }
    }


    return std::make_pair(entry_is_valid, line_entry);
} 

// Helper function to print a GCode entry out of a GCodeLineEntry
std::string GCodeLineEntry_to_string(const GCodeLineEntry& input) {
    std::ostringstream out;
    out <<  "G" << input.G
        << " X" << input.X
        << " Y" << input.Y;
    out.precision(8);
    out << " E" << input.E << std::endl;
    return out.str();
}

void GCodeProcessor::process() {
    std::size_t line_number = 0;
    for (const auto& it : InputFileLines_) {
        auto inserted_entry(InputEntriesStack_->push(interpret_entry(split_string(it))));
        if (inserted_entry.first)
            std::cout << "Entry has been inserted in line " << ++line_number << std::endl;
//        if (interpreted_entry.first) {
//            std::cout << GCodeLineEntry_to_string(interpreted_entry.second);
//            std::cout << it << std::endl << std::endl;
//        }
    }
}

void GCodeProcessor::print() const {
    for (const auto& it : InputFileLines_) {
        std::cout << it << std::endl;
    }
}
