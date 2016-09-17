/// \file   GCodeLineEntry.h
/// \author Paolo Di Giglio

#ifndef  GCode_Line_Entry_h
#define  GCode_Line_Entry_h

/// Holds the parameter of the extruder read from the input `.gcode` file.
struct GCodeLineEntry {
    /// The extruder index.
    short  G;
    /// The _x_ coordinate.
    double X;
    /// The _y_ coordinate.
    double Y;
    /// Length of the filament to extrude.
    double E;

    /// \brief Constructor.
    /// \param g The _G_ (extruder index) entry.
    /// \param x The _X_ (_x_ coordinate) entry.
    /// \param y The _Y_ (_y_ coordinate) entry.
    /// \param e The filament length to push out.
    explicit GCodeLineEntry(short g, double x, double y, double e) noexcept :
        G(g), X(x), Y(y), E(e)
    {}

    /// _Default_ constructor.
    explicit GCodeLineEntry() = default;

    /// @brief Distance between the coordinates of two entries.
    /// @param A The first coordinate.
    /// @param B The second coordinate.
    /// @attention It's a `static` member variable just because I want it to be in the `GCodeLineEntry` namespace.
    static double angle(const GCodeLineEntry& A, const GCodeLineEntry& B, const GCodeLineEntry& C) noexcept;

    /// @brief Angle _ABC_ (in degrees) between two segments (i.e. three points).
    /// @param A The first point.
    /// @param B The second point.
    /// @param C The third point.
    /// @attention It's a `static` member variable just because I want it to be in the `GCodeLineEntry` namespace.
    static double distance(const GCodeLineEntry& A, const GCodeLineEntry& B) noexcept;

};

#endif
