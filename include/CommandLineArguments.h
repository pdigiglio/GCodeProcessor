///    @file  CommandLineArguments.h
///    @date  09/12/16
///  @author  Paolo Di Giglio (github.com/pdigiglio),
///           <p.digiglio91@gmail.com>

#ifndef  Command_Line_Arguments_h
#define  Command_Line_Arguments_h

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

    /// Returns the parsed GCode filename.
    const std::string& fileName() const
    { return FileName_; }

    /// Returns the parsed extruder angle (in degrees).
    const double angle() const
    { return Angle_; }

    /// Returns the parsed extruder travel length (in millimeters).
    const double length() const
    { return Length_; }

private:
    /// GCode file name.
    const std::string FileName_;
    /// Extruder angle.
    const double Angle_;
    /// Extruder travel length.
    const double Length_;
};

#endif
