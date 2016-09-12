///    @file  CommandLineArguments.h
///    @date  09/12/16
///  @author  Paolo Di Giglio (github.com/pdigiglio),
///           <p.digiglio91@gmail.com>

#ifndef  Command_Line_Arguments_h
#define  Command_Line_Arguments_h

#include "TriggerParameters.h"

#include <string>

/// @brief Class to parse the command line arguments.
/// @details The program expects three options:
/// \code{.sh}
/// ./GCodeProcessor --file <file> --angle <angle> --length <length>
/// \endcode
/// If any of the arguments is missing or more parameters are
/// issued, the parser will `throw`.
class CommandLineArguments {
public:
    /// Constructor.
    /// @param argc Argument count.
    /// @param argv Argument vector.
    explicit CommandLineArguments(int argc, const char *argv[]);

    /// _Default_ constructor.
    explicit CommandLineArguments()  = default;
    /// _Default_ destructor.
    ~CommandLineArguments()          = default;

    /// _Default_ move assignment operator.
    CommandLineArguments& operator=(CommandLineArguments&&) = default;

    /// Returns the parsed GCode filename (_lvalue_ version).
    const std::string& fileName() const &
    { return FileName_; }

    /// Moves the parsed GCode filename (_rvalue_ version).
    std::string&& fileName() &&
    { return std::move(FileName_); }

    /// Returns the parsed extruder angle (in degrees).
    const double angle() const
    { return TriggerParameters_.Angle; }

    /// Returns the parsed extruder travel length (in millimeters).
    const double length() const
    { return TriggerParameters_.Length; }

    /// Returns the parsed trigger parameters (_lvalue_ version).
    const TriggerParameters& triggerParameters() const &
    { return TriggerParameters_; }
    
    /// Moves the parsed trigger parameters (_rvalue_ version).
    TriggerParameters&& triggerParameters() &&
    { return std::move(TriggerParameters_); }

private:
    /// GCode file name.
    std::string FileName_;

    /// Parsed trigger parameters.
    TriggerParameters TriggerParameters_;
};

#endif
