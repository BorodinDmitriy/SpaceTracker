#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QException>

#include "curl/curl.h"

class BaseException : public QException
{

};

class MemoryAllocationError : public BaseException
{
    public:
        MemoryAllocationError();
        virtual const char *what() const throw();
};

class OutOfRangeError : public BaseException
{
    public:
        OutOfRangeError();
        virtual const char *what() const throw();
};

class DivideByZeroError : public BaseException
{
    public:
        DivideByZeroError();
        virtual const char *what() const throw();
};

class VoidDelete : public BaseException
{
    public:
        VoidDelete();
        virtual const char *what() const throw();
};

class NullPointer : public BaseException
{
    public:
        NullPointer();
        virtual const char *what() const throw();
};

class DataBaseOpen : public BaseException
{
    public:
        DataBaseOpen();
        virtual const char *what() const throw();
};

class SQLiteError : public BaseException
{
    public:
        SQLiteError();
        virtual const char *what() const throw();
};

class FileExistError: public BaseException
{
    public:
        FileExistError(){}
        const char* what() const throw();
};
class OutOfMemoryError: public BaseException
{
    public:
        OutOfMemoryError(){}
        const char* what() const throw();
};


class CurlError: public BaseException
{
    public:
        CurlError(){}
        const char* what() const throw();
};


class CurlErrorR: public BaseException
{
    char errbuf[CURL_ERROR_SIZE];
    public:
        CurlErrorR(char* buf)
        {
            memcpy(errbuf,buf, CURL_ERROR_SIZE);
        }
        const char* what() const noexcept {return errbuf;}
};

class LoginError: public BaseException
{
    public:
        LoginError(){}
        const char* what() const throw();
};

class SGP4Error : public BaseException
{
    public:
        SGP4Error();
        virtual const char *what() const throw();
};

#endif // EXCEPTIONS_H
