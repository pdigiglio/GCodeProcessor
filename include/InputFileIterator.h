/// \file

#ifndef  Input_File_Iterator_h
#define  Input_File_Iterator_h

#include "GCodeLineEntry.h"

#include <iterator>
#include <sstream>
#include <string>

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

    /// Construct and read the first line in
    /// \param is ifstream to read from
    InputFileIterator(istream_type& is) : InputStream_(&is) { ++(*this); };

    /// Deference operator
    /// \return Value_
    const std::string operator*() const
    { return Value_; };

    /// Arrow iterator
    /// \return `i->m` is the same as `(*i).m`
    decltype(auto) operator->() const
    { return (*this).operator*(); };

    /// pre-increment operator (read line in)
    InputFileIterator& operator++();

    /// post-increment operator (read line in by calling `++(*this)`)
    InputFileIterator operator++(int);

    /// Returns just an empty iterator
    static const InputFileIterator& end()
    { static InputFileIterator IFI_END; return IFI_END; }

    /// equality operator; checks if pointers to streams are equal
    friend const bool operator==(const InputFileIterator& lhs, const InputFileIterator& rhs)
    { return lhs.InputStream_ == rhs.InputStream_; }

private:

    /// input stream pointer to file being read in by `this`
    istream_type* InputStream_;

    /// currently loaded line
    std::string Value_;

};

/// inequality operator
inline const bool operator!=(const InputFileIterator& lhs, const InputFileIterator& rhs)
{ return !(lhs == rhs); }

#endif
