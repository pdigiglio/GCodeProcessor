/// \file    GCodeLineEntryStack.h
/// \date    08/31/16
/// \author  Paolo Di Giglio (github.com/pdigiglio),
///          <p.digiglio91@gmail.com>

#ifndef  Trigger_Parameters_h
#define  Trigger_Parameters_h

/// Keeps the parameters of the extruder movements.
struct TriggerParameters {
    /// The extruder travel lenght in the first segment (in _millimeters_).
    double Length;
    /// The extruder angle between two segments in _degrees_ (this __must__ be
    /// between _0_ and _180_).
    double Angle;

    /// Constructor.
    /// l   The extruder travel length in _mm_.
    /// a_d The extruder angle in _degrees_.
    explicit TriggerParameters(double l, double a_d) noexcept
        : Length(l), Angle(a_d)
    {}
    
    /// _Default_ constructor.
    explicit TriggerParameters() = default;
    /// _Default_ destructor.
    ~TriggerParameters()         = default;

    /// _Deleted_ copy constructor.
    TriggerParameters(const TriggerParameters&) = delete;
    /// _Default_ move constructor.
    TriggerParameters(TriggerParameters&&)      = default;
    /// _Deleted_ copy assignment operator.
    TriggerParameters& operator=(const TriggerParameters&) = delete;
    /// _Defatult_ move assignment operator.
    TriggerParameters& operator=(TriggerParameters&&)      = default;
};

/// Less-than operator.
inline const bool operator<(const TriggerParameters& lhs, const TriggerParameters& rhs)
{ return (lhs.Length < rhs.Length) && (lhs.Angle < rhs.Angle); }

#endif
