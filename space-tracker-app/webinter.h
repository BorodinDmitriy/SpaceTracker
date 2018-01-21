#ifndef WEBINTER_H
#define WEBINTER_H

#include <QList>
#include <string>
#include <stdio.h>
#include <iostream>
#include <QDate>

#include "curl/curl.h"
#include "information.h"
#include "tleparser.h"
#include "exceptions.h"
#include "config.h"

class WebInter
{
    public:
        WebInter();
        ~WebInter();
        QList<Information> loadAllTLE(const Date &);
        QList<Information> loadTLE(const unsigned long &id, const Date &);
    private:
        CURL *curl;
        CURLcode res;
        FILE *f;
        std::string str;
        const char *errmes = WEB_INTER_ERR_MESSAGE;
        char errbuf[CURL_ERROR_SIZE];
        MemoryStruct chunk;

        std::string formString(const Date &dt, int type, const unsigned long id); // type=1 - один TLE, 0 - все
};

#endif // WEBINTER_H
