/// @file GCodeProcessor.cpp
/// @author  Paolo Di Giglio (github.com/pdigiglio),
///          <p.digiglio91@gmail.com>


//#include <cassert>

#include "GCodeProcessor.h"

#include "CommandLineArguments.h"
#include "GCodeLineEntry.h"
#include "GCodeLineEntryStack.h"
#include "InputFileIterator.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

GCodeProcessor::GCodeProcessor(CommandLineArguments&& cmd_line_args) :
    InputFileName_(std::forward<CommandLineArguments>(cmd_line_args).fileName()),
    InputEntriesStack_(std::make_unique<GCodeLineEntryStack>(std::forward<CommandLineArguments>(cmd_line_args).triggerParameters()))
{
    // Count file lines
    int num_lines = 0;
    std::ifstream input_file(InputFileName_, std::ios::in);
    std::for_each(InputFileIterator(input_file), InputFileIterator::end(),
            [&](const auto& l) { ++num_lines; });

    // Print number of lines
    std::cerr << " >> Input file length: " << num_lines << " lines." << std::endl;

    // Check for invalid input
    if (num_lines < 2)
        throw std::invalid_argument("File is less than 2 lines long: too short to be processed.");
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
    // flag to keep track of whether the line is interesting
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
    out << " E" << input.E;

    // < Marker to identify added lines
    out << " ; interpolated ";
    return out.str();
}

// Shifts the content of a vector
template <typename T>
void slide_back(std::vector<T>& v, const T& entry) {
    v.erase(v.cbegin());
    v.emplace_back(entry);
}

void GCodeProcessor::process() {
    // Open input file
    std::ifstream input_file(InputFileName_, std::ios::in);

    // File iterator
    auto it = InputFileIterator(input_file);

    // Temporary vector to hold 2 lines
    std::vector<std::string> InputFileLines_;
    InputFileLines_.reserve(2);

    // Manually insert the first two lines
    InputFileLines_.emplace_back(*it); ++it;
    InputFileLines_.emplace_back(*it); ++it;

    // Counter for the insertions
    unsigned insertions = 0;
    // Loop over the rest of the input file
    for ( ; it != InputFileIterator::end(); ++it) {
        auto inserted_entry(InputEntriesStack_->push(interpret_entry(split_string(*it))));

        // Print the cached line
        std::cout << InputFileLines_[0] << std::endl;
        // If an interpolation happened, print the line
        if (inserted_entry.first) {
            std::cout << GCodeLineEntry_to_string(inserted_entry.second) << std::endl;
            ++insertions;
        }

        slide_back(InputFileLines_, *it);
    }

    // Manually print the last two lines of the file
    std::cout << InputFileLines_[0] << std::endl;
    std::cout << InputFileLines_[1] << std::endl;

    std::cerr << " >> Inserted lines:    " << insertions << std::endl;
}
