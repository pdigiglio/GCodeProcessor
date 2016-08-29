/// \file

#ifndef  GCode_Processor_h
#define  GCode_Processor_h

#include <string>
#include <vector>

class GCodeProcessor {
public:
    /// Constructor.
    /// Reads the input file in.
    /// \param input_file_name The name of the file to read in.
    explicit GCodeProcessor(const std::string& input_file_name);

    /// _Default_ destructor.
    ~GCodeProcessor() = default;

    /// _Deleted_ copy constructor.
    GCodeProcessor(const GCodeProcessor&)                 = delete;
    /// _Deleted_ copy assignment operator.
    GCodeProcessor& operator=(const GCodeProcessor&)      = delete;

    /// Process the input file.
    void process();

    /// Prints the read-in lines.
    void print() const;
private:
    std::vector<std::string> InputFileLines_;
};

#endif
