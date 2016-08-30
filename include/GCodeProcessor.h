/// \file

#ifndef  GCode_Processor_h
#define  GCode_Processor_h

#include <string>
#include <vector>

/// Class to read in and process a `.gcode` file.
class GCodeProcessor {
public:
    /// \brief   Constructor.
    /// \details Reads the input file in and stores the lines in a `std::vector`.
    /// \param input_file_name The name of the file to read in.
    explicit GCodeProcessor(const std::string& input_file_name);

    /// _Default_ destructor.
    ~GCodeProcessor() = default;

    /// _Deleted_ copy constructor.
    GCodeProcessor(const GCodeProcessor&)            = delete;
    /// _Deleted_ move constructor.
    GCodeProcessor(GCodeProcessor&&)                 = delete;
    /// _Deleted_ copy assignment operator.
    GCodeProcessor& operator=(const GCodeProcessor&) = delete;
    /// _Deleted_ move assignment operator.
    GCodeProcessor& operator=(GCodeProcessor&&)      = delete;

    /// Process the input file.
    void process();

    /// Prints the read-in lines to the `stdout`.
    void print() const;
private:
    /// The vector of read-in lines.
    std::vector<std::string> InputFileLines_;
    // std::unique_ptr InputEntriesStack_;
};

#endif
