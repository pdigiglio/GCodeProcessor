/**
 *
 *    @file  GCodeLineEntryStack.cpp
 *   @brief  
 *
 *    @date  08/30/16
 *  @author  Paolo Di Giglio (github.com/pdigiglio),
 *           <p.digiglio91@gmail.com>
 *
 */

#include "GCodeLineEntryStack.h"

#include "GCodeLineEntry.h"

#include <cmath>
#include <utility>
#include <vector>

#include <iostream>

GCodeLineEntryStack::GCodeLineEntryStack(std::size_t stack_length, TriggerParameters&& trigger_params) :
    StackLength_(stack_length),
    MinimumTriggerParameters_(std::move(trigger_params))
{
    Stack_.reserve(StackLength_);
    for (std::size_t i = 0; i < StackLength_; ++i)
        Stack_.push_back(std::make_pair(false, GCodeLineEntry{}));
}

void GCodeLineEntryStack::slide_back(const std::pair<bool, GCodeLineEntry>& entry)
{
    // Erase the beginning
    Stack_.erase(Stack_.begin());
    // Add the entry
    Stack_.emplace_back(entry);
}

// Helper function to check if all the first entries of the vector entries
// are true.
const bool is_true(const std::vector<std::pair<bool, GCodeLineEntry>>& input)
{
    bool vector_is_true = true;
    for (const auto& it : input)
        vector_is_true &= it.first;

    // If one of the entries is false, this will return false
    return vector_is_true;
}

// Helper function to get the value of pi.
constexpr double pi()
{ return std::atan(1) * 4; }

// Helper function to calculate the distance between the 
// coordinates of two entries
double distance(const GCodeLineEntry& A, const GCodeLineEntry& B)
{
    auto delta_x = A.X - B.X;
    auto delta_y = A.Y - B.Y;

    return std::sqrt((delta_x * delta_x) + (delta_y * delta_y));
}

// Helper function to calculate the angle (in degrees) between the 
// coordinates of two entries
double angle(const GCodeLineEntry& A, const GCodeLineEntry& B, const GCodeLineEntry& C)
{
    auto ab_dot_bc = (A.X - B.X) * (B.X - C.X) + (A.Y - B.Y) * (B.Y - C.Y);
    return 180 * std::acos(ab_dot_bc / (distance(A, B) * distance(B, C))) / pi();
}

decltype(auto) evaluate_parameters(const std::vector<std::pair<bool, GCodeLineEntry>>& input)
{
    return TriggerParameters(distance(input[0].second, input[1].second),
                             angle(input[0].second, input[1].second, input[2].second));
}

std::pair<bool, GCodeLineEntry> GCodeLineEntryStack::push(const std::pair<bool, GCodeLineEntry>& entry)
{
    // Slide the entries down
    slide_back(entry);

    // Check if adjacent entries are candidates for fitting
    if (is_true(Stack_))
        return interpolate();

    // Return a pair whose first entry is false
    return std::make_pair(false, Stack_[0].second);
}

std::pair<bool, GCodeLineEntry> GCodeLineEntryStack::interpolate() const
{
    if (evaluate_parameters(Stack_) < MinimumTriggerParameters_) {
        std::cerr << "interpolation needed" << std::endl;
        return std::make_pair(true, GCodeLineEntry{});
    }

    return std::make_pair(false, GCodeLineEntry{});
}
