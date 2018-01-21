#include "webinter.h"
#include "config.h"


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
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_URL, LOGIN_URL))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_POST, 1))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_POSTFIELDS, LOGIN_PARAMETERS))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_HEADER, 0))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_COOKIEJAR, COOKIE_JAR))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_COOKIEFILE, COOKIE_TYPE))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_USERAGENT, CURL_AGENT))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl,  CURLOPT_SSLCERTTYPE, CURL_CERT_TYPE))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_setopt(curl,  CURLOPT_SSLCERT, CURL_CERT_PATH))
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

std::string WebInter::formString(const Date &dt, int type, const unsigned long id = 0)
{
    QDate d1(dt.Year, dt.Mounth, dt.Day);
    QDate d2 = d1.addDays(-1);
    std::string fsd = d1.toString(QString("yyyy-MM-dd")).toStdString();
    std::string scd = d2.toString(QString("yyyy-MM-dd")).toStdString();

    std::string q = LOAD_TLE_URL;
    q += scd;
    q += "--";
    q += fsd;
    if (type == 1) {
       q += "/TLE_LINE1/~~1%";
       q += std::to_string(id);
    }
    q += LIMIT_LOAD_TLE_STRING;

    return q;
}


QList <Information> WebInter::loadAllTLE(const Date &dt)
{
    if (chunk.memory  != 0)
    {
        free(chunk.memory);
        chunk.memory = 0;
    }

    chunk.memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;
    if (CURLE_OK != curl_easy_setopt(curl,  CURLOPT_WRITEDATA, (void *)&chunk))
    {
        throw CurlError();
    }
    QList<Information> resInfo;

    std::string q = formString(dt,0);
    if (CURLE_OK != curl_easy_setopt(curl, CURLOPT_URL, q.c_str()))
    {
        throw CurlError();
    }
    if (CURLE_OK != curl_easy_perform(curl))
    {
        throw CurlErrorR(errbuf);
    }
    if (!strcmp(errmes, chunk.memory))
    {
        throw LoginError();
    }
    TleParser pars1;
    resInfo = pars1.getTLE(chunk.memory);
    return resInfo;
}


QList<Information> WebInter::loadTLE(const unsigned long &id, const Date &dt)
{
    if(chunk.memory != 0)
    {
        free(chunk.memory);
        chunk.memory = 0;
    }

    chunk.memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;
    if(CURLE_OK != curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk))
    {
        throw CurlError();
    }
    QList<struct Information> resInfo;
    std::string q = formString(dt,1,id);
    if(CURLE_OK != curl_easy_setopt(curl, CURLOPT_URL, q.c_str()))
    {
        throw CurlError();
    }

    if(CURLE_OK != curl_easy_perform(curl))
    {
        throw CurlErrorR(errbuf);
    }

    TleParser pars1;
    resInfo = pars1.getTLE(chunk.memory);
    return resInfo;
}
