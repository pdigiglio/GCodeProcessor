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

#include <utility>
#include <vector>

GCodeLineEntryStack::GCodeLineEntryStack()
{
    Stack_.reserve(2);
    push(std::make_pair(false, GCodeLineEntry{}));
}

std::pair<bool, GCodeLineEntry> GCodeLineEntryStack::push(const std::pair<bool, GCodeLineEntry>& entry)
{
    // Slide the entries down
    Stack_[0] = Stack_[1];
    Stack_[1] = entry;

    // Check if adjacent entries are candidates for fitting
    if (Stack_[0].first && Stack_[1].first)
        return interpolate();

    // Return a pair whose first entry is false
    return std::make_pair(false, Stack_[0].second);
}

std::pair<bool, GCodeLineEntry> GCodeLineEntryStack::interpolate() const
{
    return std::make_pair(true, GCodeLineEntry{});
}
