/// \file

#ifndef  Input_File_Iterator_h
#define  Input_File_Iterator_h

#include "GCodeLineEntry.h"

#include <iterator>
#include <sstream>
#include <string>

/// \brief Reads an input file line by line.
class InputFileIterator : public std::iterator<std::input_iterator_tag, std::string>
{

public:

    // defined for convenience
    using char_type    = typename std::string::value_type;
    using traits_type  = typename std::string::traits_type;
    using istream_type = std::basic_istream<char_type, traits_type>;

private:

    /// Default constructor (private).
    InputFileIterator() : InputStream_(nullptr) {};

public:

    /// \brief Construct and read the first line in.
    /// \param is Input stream to read from.
    InputFileIterator(istream_type& is) : InputStream_(&is) { ++(*this); };

    /// \brief Deference operator.
    /// \return The line that is currently loaded in `Value_` (i.e. a copy of `Value_`).
    const std::string operator*() const
    { return Value_; };

    /// \brief Arrow iterator.
    /// \return `i->m` is the same as `(*i).m`.
    decltype(auto) operator->() const
    { return (*this).operator*(); };

    /// Pre-increment operator (read line in).
    InputFileIterator& operator++();

    /// Post-increment operator (read line in).
    InputFileIterator operator++(int);

    /// Returns an empty iterator.
    static const InputFileIterator& end()
    { static InputFileIterator IFI_END; return IFI_END; }

    /// Equality operator; checks if pointers to streams are equal.
    friend const bool operator==(const InputFileIterator& lhs, const InputFileIterator& rhs)
    { return lhs.InputStream_ == rhs.InputStream_; }

private:

    /// Input stream pointer to file being read in by `this`.
    istream_type* InputStream_;

    /// Currently loaded line.
    std::string Value_;
};

/// inequality operator
inline const bool operator!=(const InputFileIterator& lhs, const InputFileIterator& rhs)
{ return !(lhs == rhs); }

#endif
