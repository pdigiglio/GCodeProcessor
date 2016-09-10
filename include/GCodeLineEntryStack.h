/// \file    GCodeLineEntryStack.h
/// \date    08/30/16
/// \author  Paolo Di Giglio (github.com/pdigiglio),
///          <p.digiglio91@gmail.com>

#ifndef  GCode_Line_Entry_Stack_h
#define  GCode_Line_Entry_Stack_h

#include "GCodeLineEntry.h"
#include "TriggerParameters.h"

#include <utility>
#include <vector>

/// \brief   Stack of `GCodeLineEntry`'s.
/// \details Keeps track of the last two read-in line entries and
/// interpolates among them if necessary.
class GCodeLineEntryStack
{
public:
    /// Constructor.
    explicit GCodeLineEntryStack(std::size_t stack_length, const TriggerParameters& trigger_params);

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

    /// \brief Pushes the new value in the stack discarding the last one and,
    /// possibly, interpolates the stack entries.
    /// \param entry The enry to push in the stack.
    /// \return A pair whose entries have to be interpreted as follows:
    ///  * `pair.first ` tells whether the stack entries have been interpolated;
    ///  * `pair.second` the interpolated `GCodeLineEntry`. If an interpolation
    /// didn't take place, this is just a dummy value and __must__ be ignored.
    std::pair<bool, GCodeLineEntry> push(const std::pair<bool, GCodeLineEntry>& entry);

    /// Returns the internal stack.
    decltype(auto) getStack() const
    { return Stack_; }

private:
    /// The two temporary elements to interpolate between.
    std::vector<std::pair<bool, GCodeLineEntry>> Stack_;

    /// The length of the stack.
    const std::size_t StackLength_;

    /// The threshold for the parameters to trigger the interpolation.
    TriggerParameters MinimumTriggerParameters_;

    /// Interpolates between the entries of the `Stack_`.
    std::pair<bool, GCodeLineEntry> interpolate() const;

    /// Slides the stack entries back and puts `entry` on top.
    /// \param entry The entry to stack on top.
    void slide_back(const std::pair<bool, GCodeLineEntry>& entry);
};

#endif
