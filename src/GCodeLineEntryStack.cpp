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
#include "TriggerParameters.h"

#include <utility>
#include <vector>

GCodeLineEntryStack::GCodeLineEntryStack(TriggerParameters&& trigger_params) :
    MinimumTriggerParameters_(std::move(trigger_params))
{
    Stack_.reserve(3);
    for (std::size_t i = 0; i < 3; ++i)
        Stack_.push_back(std::make_pair(false, GCodeLineEntry{}));
}

template<typename T>
void slide_back(std::vector<T>&v, const T& entry)
{
    // Erase the beginning
    v.erase(v.begin());
    // Add the entry
    v.emplace_back(entry);
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


std::pair<bool, GCodeLineEntry> GCodeLineEntryStack::push(const std::pair<bool, GCodeLineEntry>& entry)
{
    // Slide the entries down
    slide_back(Stack_, entry);

    // Check if adjacent entries are candidates for fitting
    if (is_true(Stack_))
        return interpolate();

    // Return a pair whose first entry is false
    return std::make_pair(false, GCodeLineEntry{});
}

// Helper function to get the parameters of the movement
decltype(auto) evaluate_parameters(const std::vector<std::pair<bool, GCodeLineEntry>>& input)
{
    return TriggerParameters(
            GCodeLineEntry::distance(input[0].second, input[1].second),
            GCodeLineEntry::angle(input[0].second, input[1].second, input[2].second));
}

std::pair<bool, GCodeLineEntry> GCodeLineEntryStack::interpolate() const
{
    if (evaluate_parameters(Stack_) < MinimumTriggerParameters_)
        return std::make_pair(true,
                GCodeLineEntry::point_between(Stack_[0].second, Stack_[1].second, 1.));

    return std::make_pair(false, GCodeLineEntry{});
}
