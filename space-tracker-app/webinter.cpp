#include "webinter.h"

static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *)userp;
    mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL)
        throw MemoryAllocationError();
    memcpy( &(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = '\0';
    return realsize;
}

WebInter::WebInter()
{
    chunk.size = 0;
    chunk.memory = 0;
    curl = curl_easy_init();
    if (!curl)
    {
        throw CurlError();
    }
    if(CURLE_OK != curl_easy_setopt(curl,CURLOPT_ERRORBUFFER, errbuf))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_URL, "https://www.space-track.org/ajaxauth/login"))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_POST, 1))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "identity=catkiller95@gmail.com&password=catkiller19950214"))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_HEADER, 0))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookie"))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookie"))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0"))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl,  CURLOPT_SSLCERTTYPE, "PEM"))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl,  CURLOPT_SSLCERT, "D:/QtVit/Qt5.1.0/Tools/QtCreator/bin/TEST/bookingcar.pem"))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_perform(curl))
    {
        throw CurlErrorR(errbuf);
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_POST, 0))
    {
        throw CurlError();
    }
    //std::cout<<"object created";
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback))
    {
        throw CurlError();
    }
    return;
}

WebInter::~WebInter()
{
    free(chunk.memory);
    chunk.size = 0;
    curl_easy_cleanup(curl);
    return;
}


QList <Information> WebInter::loadAllTLE(const Date &dt)
{
    if (chunk.memory  != 0)
    {
        free(chunk.memory);
        chunk.memory = 0;
    }
    //std::string date = "";
    //date += atoi(dt.Day);
    //date += ":";
    //date += atoi(dt.Mounth);
    //date += ":";
    //date += atoi(dt.Year);
    QDate d1(dt.Year, dt.Mounth, dt.Day);
    QDate d2 = d1.addDays(-1);
    std::string fsd = d1.toString(QString("yyyy-MM-dd")).toStdString();
    std::string scd = d2.toString(QString("yyyy-MM-dd")).toStdString();
    chunk.memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;
    if (CURLE_OK != curl_easy_setopt(curl,  CURLOPT_WRITEDATA, (void *)&chunk))
    {
        throw CurlError();
    }
    QList<Information> resInfo;
    std::string q = "https://www.space-track.org/basicspacedata/query/class/tle_publish/PUBLISH_EPOCH/";
    q += scd;
    q += "--";
    q += fsd;
    q += "/orderby/PUBLISH_EPOCH%20asc/limit/10/format/tle/metadata/false";
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_URL, q.c_str()))
    {
        throw CurlError();
    }
    //curl_easy_setopt(curl, CURLOPT_URL, "https://www.space-track.org/basicspacedata/query/class/tle_latest/limit/10/format/3le");
    //https://www.space-track.org/basicspacedata/query/class/boxscore/format/stream
    //curl_easy_setopt(curl, CURLOPT_URL, "https://www.space-track.org/basicspacedata/query/class/boxscore/format/json");
    if (CURLE_OK != curl_easy_perform(curl))
    {
        throw CurlErrorR(errbuf);
    }
    //std::cout<<"#######################IN CHUNK #########################\n";
    //std::cout<<chunk.memory;
    if (!strcmp(errmes, chunk.memory))
    {
        throw LoginError();
    }
    TleParser pars1;
    resInfo = pars1.getTLE(chunk.memory);
    return resInfo;
}

QList<Information> WebInter::loadAllSSR(const Date &dt)
{
    QList<Information> resInfo;
    return resInfo;
}

QList<Information> WebInter::loadSSR(const unsigned long &id, const Date &dt)
{
    QList<Information> resInfo;
    return resInfo;
}

QList<Information> WebInter::loadTLE(const unsigned long &id, const Date &dt)
{
    if(chunk.memory != 0)
    {
        free(chunk.memory);
        chunk.memory = 0;
    }
    //std::string date = "";
    //date += atoi(dt.Day);
    //date += ":";
    //date += atoi(dt.Mounth);
    //date += ":";
    //date += atoi(dt.Year);
    QDate d1(dt.Year, dt.Mounth, dt.Day);
    QDate d2 = d1.addDays(-1);
    std::string fsd = d1.toString(QString("yyyy-MM-dd")).toStdString();
    std::string scd = d2.toString(QString("yyyy-MM-dd")).toStdString();
    chunk.memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;
    if(CURLE_OK != curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk))
    {
        throw CurlError();
    }
    QList<struct Information> resInfo;
    std::string q = "https://www.space-track.org/basicspacedata/query/class/tle_publish/PUBLISH_EPOCH/";
    q += scd;
    q += "--";
    q += fsd;
    q += "/TLE_LINE1/~~1%";
    q += std::to_string(id);
    q += "/orderby/PUBLISH_EPOCH%20asc/limit/10/format/tle/metadata/false";
    if(CURLE_OK != curl_easy_setopt(curl, CURLOPT_URL, q.c_str()))
    {
        throw CurlError();
    }
    //curl_easy_setopt(curl, CURLOPT_URL, "https://www.space-track.org/basicspacedata/query/class/tle_latest/limit/10/format/3le");
    //https://www.space-track.org/basicspacedata/query/class/boxscore/format/stream
    //curl_easy_setopt(curl, CURLOPT_URL, "https://www.space-track.org/basicspacedata/query/class/boxscore/format/json");
    if(CURLE_OK != curl_easy_perform(curl))
    {
        throw CurlErrorR(errbuf);
    }
    //std::cout<<"#######################IN CHUNK #########################\n";
    //std::cout<<chunk.memory;
    TleParser pars1;
    resInfo = pars1.getTLE(chunk.memory);
    return resInfo;
}
