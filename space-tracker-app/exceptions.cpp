#include "exceptions.h"

MemoryAllocationError::MemoryAllocationError(){

}

const char *MemoryAllocationError::what() const throw()
{
     return "memory allocation error \n";
}
OutOfRangeError::OutOfRangeError()
{

}

const char *OutOfRangeError::what() const throw()
{
     return "out of range error \n";
}

DivideByZeroError::DivideByZeroError()
{

}

const char *DivideByZeroError::what() const throw()
{
     return "divide by zero error \n";
}

VoidDelete::VoidDelete()
{

}

const char *VoidDelete::what() const throw()
{
    return "delete null pointer";
}

NullPointer::NullPointer()
{

}

const char *NullPointer::what() const throw()
{
    return "null pointer, don't allocate memory";
}

DataBaseOpen::DataBaseOpen()
{

}

const char *DataBaseOpen::what() const throw()
{
    return "Can't open database";
}

SQLiteError::SQLiteError()
{

}

const char *SQLiteError::what() const throw()
{
    return "SQLite error inquiry";
}

SGP4Error::SGP4Error()
{

}

const char *SGP4Error::what() const throw()
{
    return "SGP4 error date";
}
