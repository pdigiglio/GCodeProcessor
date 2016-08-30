/**
 *
 *    @file  GCodeLineEntryStack.h
 *   @brief  
 *
 *    @date  08/30/16
 *  @author  Paolo Di Giglio (github.com/pdigiglio),
 *           <p.digiglio91@gmail.com>
 *
 */

#ifndef  GCode_Line_Entry_Stack_h
#define  GCode_Line_Entry_Stack_h

#include "GCodeLineEntry.h"

#include <utility>
#include <vector>

class GCodeLineEntryStack
{
public:
    /// Constructor.
    explicit GCodeLineEntryStack();

    /// _Default_ destructor.
    ~GCodeLineEntryStack()         = default;

    /// _Deleted_ copy constructor.
    GCodeLineEntryStack(const GCodeLineEntryStack&) = delete;
    /// _Deleted_ move constructor.
    GCodeLineEntryStack(GCodeLineEntryStack&&)      = delete;
    /// _Deleted_ copy assignment operator.
    GCodeLineEntryStack& operator=(const GCodeLineEntryStack&) = delete;
    /// _Deleted_ move assignment operator.
    GCodeLineEntryStack& operator=(GCodeLineEntryStack&&)      = delete;

    std::pair<bool, GCodeLineEntry> push(const std::pair<bool, GCodeLineEntry>& entry);

    decltype(auto) getStack() const
    { return Stack_; }

private:
    /// The two temporary elements to interpolate between.
    std::vector<std::pair<bool, GCodeLineEntry>> Stack_;

    /// Interpolates between the entries of the Stack_.
    std::pair<bool, GCodeLineEntry> interpolate() const;
};

#endif
