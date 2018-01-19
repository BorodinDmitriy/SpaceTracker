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

class WebInter
{
    public:
        WebInter();
        ~WebInter();
        QList<Information> loadAllTLE(const Date &);
        QList<Information> loadAllSSR(const Date &);
        QList<Information> loadSSR(const unsigned long &id, const Date &);
        QList<Information> loadTLE(const unsigned long &id, const Date &);
    private:
        CURL *curl;
        CURLcode res;
        FILE *f;
        std::string str;
        //size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
        const char *errmes = "<html>\n<body>\n\t\n\t\t<p><p>You must be logged in to complete this action</p></p>\n\n</body>\n</html>";
        char errbuf[CURL_ERROR_SIZE];
        MemoryStruct chunk;
};

#endif // WEBINTER_H
