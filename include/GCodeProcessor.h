/// @file    GCodeProcessor.h
/// @author  Paolo Di Giglio (github.com/pdigiglio),
///          <p.digiglio91@gmail.com>

#ifndef  GCode_Processor_h
#define  GCode_Processor_h

#include "fwd/CommandLineArguments.h"

#include "GCodeLineEntryStack.h"

#include <memory>
#include <string>

/// Class to read in and process a `.gcode` file.
class GCodeProcessor {
public:
    /// @brief   Constructor.
    /// @details Reads the input file in and stores the lines in a `std::vector`.
    /// @param cmd_line_args Parsed command line arguments.
    explicit GCodeProcessor(CommandLineArguments&& cmd_line_args);

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

private:
    /// The input `.gcode` file.
    const std::string InputFileName_;

    /// The 3-element `.gcode` line entry stack.
    std::unique_ptr<GCodeLineEntryStack> InputEntriesStack_;
};

#endif
