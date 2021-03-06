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
    /// The reducef filament (only in interpolated entries)
    double R;

    /// \brief Constructor.
    /// \param g The _G_ (extruder index) entry.
    /// \param x The _X_ (_x_ coordinate) entry.
    /// \param y The _Y_ (_y_ coordinate) entry.
    /// \param e The filament length to push out.
    constexpr explicit GCodeLineEntry(short g, double x, double y, double e, double r = 0) noexcept :
        G(g), X(x), Y(y), E(e), R(r)
    {}

    /// _Default_ constructor.
    explicit GCodeLineEntry() = default;

    /// @brief Distance between the coordinates of two entries.
    /// @param A The first coordinate.
    /// @param B The second coordinate.
    /// @attention It's a `static` member variable just because I want it to be in the `GCodeLineEntry` namespace.
    /// @todo `throw` if the _G_'s don't match!
    static double angle(const GCodeLineEntry& A, const GCodeLineEntry& B, const GCodeLineEntry& C) noexcept;

    /// @brief Creates a point on the segment _AB_ with a specified distance from the second point.
    /// @param A The first coordinate.
    /// @param B The second coordinate.
    /// @param d The distance from the second point.
    /// @param red The reduction factor (between _0_ and _1_).
    /// @attention It's a `static` member variable just because I want it to be in the `GCodeLineEntry` namespace.
    /// @todo `throw` if the _G_'s don't match!
    static GCodeLineEntry point_between(const GCodeLineEntry& A, const GCodeLineEntry& B, const double d, double red = 1.) noexcept;

    /// @brief Angle _ABC_ (in degrees) between two segments (i.e. three points).
    /// @param A The first point.
    /// @param B The second point.
    /// @param C The third point.
    /// @attention It's a `static` member variable just because I want it to be in the `GCodeLineEntry` namespace.
    /// @todo `throw` if the _G_'s don't match!
    static double distance(const GCodeLineEntry& A, const GCodeLineEntry& B) noexcept;

};

#endif
