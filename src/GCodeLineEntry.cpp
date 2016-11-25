/// @file   GCodeLineEntry.h
/// @date  09/17/16
/// @author Paolo Di Giglio
///         <p.digiglio91@gmail.com>

#include "GCodeLineEntry.h"

#include <cmath>

// Helper function to get the value of pi.
constexpr inline double pi() noexcept
{ return std::atan(1) * 4; }

double GCodeLineEntry::distance(const GCodeLineEntry& A, const GCodeLineEntry& B) noexcept
{
    const auto delta_x = A.X - B.X;
    const auto delta_y = A.Y - B.Y;

    return std::sqrt((delta_x * delta_x) + (delta_y * delta_y));
}

// Helper function to calculate the angular coefficient of an extruder movement
constexpr inline double angular_coefficient(const GCodeLineEntry& A, const GCodeLineEntry& B)
{ return (B.Y - A.Y) / (B.X - A.X); }

GCodeLineEntry GCodeLineEntry::point_between(const GCodeLineEntry& A, const GCodeLineEntry& B, const double d, double red) noexcept
{
    // Angle, and magnitude of A->B
    const double angle = std::atan(angular_coefficient(A, B)) + ((B.X < A.X) ? pi() : 0.);
    const double magnitude = distance(A, B);

    return GCodeLineEntry(A.G, // !! Assuming A.G == B.G !!
            A.X + (magnitude - d) * std::cos(angle),
            A.Y + (magnitude - d) * std::sin(angle),
            A.E + red * (B.E - A.E) * (1 - d / magnitude),
            (1 - red) * (B.E - A.E) * (1 - d / magnitude));
}

double GCodeLineEntry::angle(const GCodeLineEntry& A, const GCodeLineEntry& B, const GCodeLineEntry& C) noexcept
{
    const auto ab_dot_bc = (A.X - B.X) * (B.X - C.X) + (A.Y - B.Y) * (B.Y - C.Y);
    return 180 * std::acos(ab_dot_bc / (distance(A, B) * distance(B, C))) / pi();
}
