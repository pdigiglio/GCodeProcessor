/// \file    TriggerParameters.h
/// \date    08/31/16
/// \author  Paolo Di Giglio (github.com/pdigiglio),
///          <p.digiglio91@gmail.com>

#ifndef  Trigger_Parameters_h
#define  Trigger_Parameters_h

/// Parameters of the extruder movements.
struct TriggerParameters {
    /// The extruder travel lenght in the first segment (in _millimeters_).
    double Length;
    /// @brief The extruder angle between two segments (in _degrees_).
    /// @attention This __must__ be between _0_ and _180_.
    double Angle;

    /// @brief Constructor.
    /// @param l   The extruder travel length in _mm_.
    /// @param a_d The extruder angle in _degrees_.
    constexpr explicit TriggerParameters(double l, double a_d) noexcept
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
/// @param lhs The left-hand side.
/// @param rhs The right-hand side.
inline const bool operator<(const TriggerParameters& lhs, const TriggerParameters& rhs)
{ return (lhs.Length < rhs.Length) && (lhs.Angle < rhs.Angle); }

#endif
