#include "InputFileIterator.h"

#include <fstream>
#include <sstream>
#include <string>

//-------------------------
InputFileIterator& InputFileIterator::operator++()
{
    // check if iterator reaches EOF
    if (InputStream_ and !getline(*InputStream_, Value_))
        return *this = end();

    return *this;
}

//-------------------------
InputFileIterator InputFileIterator::operator++(int)
{
    InputFileIterator prev(*this);
    // read line in
    ++(*this);
    return prev;
}
