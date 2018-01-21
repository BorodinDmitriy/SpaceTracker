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

const char *CurlError::what() const throw()
{
    return "Something went wrong with CURL";
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

const char *FileExistError::what() const throw()
{
    return "File which you try to open doesn't exist.";
}

const char *OutOfMemoryError::what() const throw() {
    return "Out of memory";
}

const char *LoginError::what() const throw() {
    return "Cant login";
}

SGP4Error::SGP4Error()
{

}

const char *SGP4Error::what() const throw()
{
    return "SGP4 error date";
}
