/// \file


#include "GCodeProcessor.h"

#include "GCodeLineEntry.h"
#include "InputFileIterator.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

GCodeProcessor::GCodeProcessor(const std::string& input_file_name) {
    std::ifstream inFile(input_file_name, std::ios::in);
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


decltype(auto) interpret_entry (const std::vector<std::string>& input) {
    // empty line entry
    GCodeLineEntry line_entry;
    bool entry_is_valid = false;

    std::string::size_type n;
    if (input[0].find('G') == 0) {
//        std::cout << std::stoi(input[0].substr(1)) << std::endl;
        line_entry.G = std::stoi(input[0].substr(1));

        if (input[1].find('X') == 0) {
//            std::cout << std::stod(input[1].substr(1)) << std::endl;
            line_entry.X = std::stod(input[1].substr(1));

            if (input[2].find('Y') == 0) {
//                std::cout << std::stod(input[2].substr(1)) << std::endl;
                line_entry.Y = std::stod(input[2].substr(1));

                if (input[3].find('E') == 0) {
//                    std::cout << std::stod(input[3].substr(1)) << std::endl;
                    line_entry.E = std::stod(input[3].substr(1));
                    entry_is_valid = true;
                }
            }
        }
    }

    return std::make_pair(entry_is_valid, line_entry);
} 

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
    for (const auto& it : InputFileLines_) {
        auto string_splitted = split_string(it);
        if (string_splitted.size() > 3) {
            auto interpreted_entry = interpret_entry(string_splitted);
            if (interpreted_entry.first) {
                std::cout << GCodeLineEntry_to_string(interpreted_entry.second);
                std::cout << it << std::endl << std::endl;
            }
        }

    }
}

void GCodeProcessor::print() const {
    for (const auto& it : InputFileLines_) {
        std::cout << it << std::endl;
    }
}
