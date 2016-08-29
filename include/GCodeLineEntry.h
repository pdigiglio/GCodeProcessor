/// \file

#ifndef  GCode_Line_Entry_h
#define  GCode_Line_Entry_h

struct GCodeLineEntry {
    short  G;
    double X;
    double Y;
    double E;

    explicit GCodeLineEntry(short g, double x, double y, double e) noexcept :
        G(g), X(x), Y(y), E(e)
    {}

    explicit GCodeLineEntry() = default;
};

#endif
