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

double GCodeLineEntry::angle(const GCodeLineEntry& A, const GCodeLineEntry& B, const GCodeLineEntry& C) noexcept
{
    const auto ab_dot_bc = (A.X - B.X) * (B.X - C.X) + (A.Y - B.Y) * (B.Y - C.Y);
    return 180 * std::acos(ab_dot_bc / (distance(A, B) * distance(B, C))) / pi();
}
