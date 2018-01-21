#include "tleparser.h"

TleParser::TleParser()
{

}

// Номер в комментариях ниже - номер элемента в строке TLE

void TleParser::setName(const char *str, TLE &tl)
{
    std::string buf;
    int i = 1;
    while ((str[i] != '\n') && (str[i] != '\r'))
    {
        buf += str[i];
        i++;
    }
    i = 0;
    while (buf[i] != '\0')
    {
        tl.name[i] = buf[i];
        i++;
    }
    tl.name[i] = '\0';
    return;
}//1

void TleParser::setID(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 2; i < 7; i++)
    {
        buf += str[i];
    }
    tl.nor_id = atoi(buf.c_str());
    return;
}  //2

void TleParser::setClass(const char *str, TLE &tl)
{
    tl.cl = str[7];
    return;
} //3

void TleParser::setINS(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 9; i < 11; i++)
    {
        buf += str[i];
    }
    int i = 0;
    while (buf[i])
    {
        tl.i_n_s[i] = buf[i];
        i++;
    }
    return;
}  //4

void TleParser::setINN(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 11; i < 14; i++)
    {
        buf += str[i];
    }
    tl.i_n_n = atoi(buf.c_str());
    return;
}  //5

void TleParser::setINP(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 14; i < 17; i++)
    {
        buf += str[i];
    }
    int i = 0;
    while (buf[i])
    {
        tl.i_n_p[i] = buf[i];
        i++;
    }
    return;
} //6

void TleParser::setEra(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 18; i < 20; i++)
    {
        buf += str[i];
    }
    int i = 0;
    while (buf[i])
    {
        tl.era[i] = buf[i];
        i++;
    }
    return;
} //7

void TleParser::setEraT(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 20; i < 32; i++)
    {
        if (((str[i] == '+') || (str[i] == '-')) && (!buf.empty()))
        {
            buf += 'E';
        }
        buf += str[i];
    }
    tl.era_t = std::strtod(buf.c_str(), 0);
    return;
} //8

void TleParser::setDer(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 33; i < 43; i++)
    {
        if (((str[i] == '+') || (str[i] == '-')) && (!buf.empty()))
        {
            buf += 'E';
        }
        buf += str[i];
    }
    tl.der = std::strtod(buf.c_str(), 0);
    return;
}  //9

void TleParser::setDer2(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 44; i < 52; i++)
    {
        if (((str[i] == '+') || (str[i] == '-')) && (!buf.empty()))
        {
            buf += 'E';
        }
        buf += str[i];
    }
    if (((buf[0] == '+') || (buf[0] == '-')))
    {
        buf.insert(1, ".");
    }
    else
    {
        buf.insert(0, ".");
    }
    tl.der2 = std::strtod(buf.c_str(), 0);
    return;
}  //10

void TleParser::setB(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 53; i < 61; i++)
    {
        if (((str[i] == '+') || (str[i] == '-')) && (!buf.empty()))
        {
            buf += 'E';
        }
        buf += str[i];
    }
    if (((buf[0] == '+') || (buf[0] == '-')))
    {
        buf.insert(1, ".");
    }
    else
    {
        buf.insert(0, ".");
    }
    tl.b = std::strtod(buf.c_str(), 0);
    return;
}  //11

void TleParser::setEfi(const char *str, TLE &tl)
{
    tl.efi = 0;
    return;
} //12

void TleParser::setNum(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 64; i < 68; i++)
    {
        buf += str[i];
    }
    tl.num = atoi(buf.c_str());
    return;
}  //13

void TleParser::setSum(const char *str, TLE &tl)
{
    tl.sum = str[68] - (int)'0';
    return;
}  //14

void TleParser::setIncl(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 8; i < 16; i++)
    {
        if (((str[i] == '+') || (str[i] == '-')) && (!buf.empty()))
        {
            buf += 'E';
        }
        buf += str[i];
    }
    tl.incl = std::strtod(buf.c_str(), 0);
    return;
} //3

void TleParser::setLg(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 17; i < 25; i++)
    {
        if (((str[i] == '+') || (str[i] == '-')) && (!buf.empty()))
        {
            buf += 'E';
        }
        buf += str[i];
    }
    tl.lg = std::strtod(buf.c_str(), 0);
    return;
}  //4

void TleParser::setEx(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 26; i < 33; i++)
    {
        if (((str[i] == '+') || (str[i] == '-')) && (!buf.empty()))
        {
            buf += 'E';
        }
        buf += str[i];
    }
    if (((buf[0] == '+') || (buf[0] == '-')))
    {
        buf.insert(1, ".");
    }
    else
    {
        buf.insert(0, ".");
    }
    tl.ex = std::strtod(buf.c_str(), 0);
    return;
}  //5

void TleParser::setArgPer(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 34; i < 42; i++)
    {
        if (((str[i] == '+') || (str[i] == '-')) && (!buf.empty()))
        {
            buf += 'E';
        }
        buf += str[i];
    }
    tl.arg_per = std::strtod(buf.c_str(), 0);
    return;
}//6

void TleParser::setAverAnom(const char *str, TLE &tl)
{
     std::string buf;
     for (int i = 43; i < 50; i++)
     {
         if (((str[i] == '+') || (str[i] == '-')) && (!buf.empty()))
         {
             buf += 'E';
         }
         buf += str[i];
     }
     tl.aver_anom = std::strtod(buf.c_str(), 0);
     return;
}//7

void TleParser::setFreq(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 52; i < 63; i++)
    {
        if (((str[i] == '+') || (str[i] == '-')) && (!buf.empty()))
        {
            buf += 'E';
        }
        buf += str[i];
    }
    tl.freq = std::strtod(buf.c_str(), 0);
    return;
}//8

void TleParser::setEraNum(const char *str, TLE &tl)
{
    std::string buf;
    for (int i = 63; i < 68; i++)
    {
        buf += str[i];
    }
    tl.era_num = atoi(buf.c_str());
    return;
}//9

void TleParser::setSum2(const char *str, TLE &tl)
{
    tl.sum_2 = str[68];
    return;
}//10

void TleParser::firstStrPars(const char *str, Information &tl)
{
    setName(str, tl.TLEI);
    return;
}

void TleParser::secondStrPars(const char *str, Information &tlIn)
{
    TLE &tl = tlIn.TLEI;
    setID(str, tl);
    setClass(str, tl);
    setINS(str, tl);
    setINN(str, tl);
    setINP(str, tl);
    setEra(str, tl);
    setEraT(str, tl);
    setDer(str, tl);
    setDer2(str, tl);
    setB(str, tl);
    setEfi(str, tl);
    setNum(str, tl);
    setSum(str, tl);
    int i = 0;
    while ((str[i] != '\n') && (str[i] != '\r'))
    {
        tlIn.TLEstr1 += str[i];
        i++;
    }
    return;
}

void TleParser::thirdStrPars(const char *str, Information &tlIn)
{
    TLE &tl = tlIn.TLEI;
    setIncl(str, tl);
    setLg(str, tl);
    setEx(str, tl);
    setArgPer(str, tl);
    setAverAnom(str, tl);
    setFreq(str, tl);
    setEraNum(str, tl);
    setSum2(str, tl);
    int i = 0;
    while ((str[i] != '\n') && (str[i] != '\r'))
    {
        tlIn.TLEstr2 += str[i];
        i++;
    }
    return;
}

Information TleParser::getOneTLE(const char *str)
{
    int i = 0;
    Information someInfo;
    secondStrPars((str + i), someInfo);
    while (str[i] != '\n')
    {
        i++;
    }
    i++;
    thirdStrPars((str + i), someInfo);
    return someInfo;
}

const char* TleParser::getNextTLE(const char *str)
{
    int i = 0;
    int count = 2;
    while (count)
    {
        if (str[i] == '\n')
        {
            count--;
        }
        i++;
    }
    if (str[i] == '\0')
    {
        return 0;
    }
    return (str + i);
}

QList<Information> TleParser::getTLE(const char *str)
{
    QList<Information> resInfo;
    Information someInfo;
    const char *bufStr = str;
    std::string str1;
    std::string str2;
    while (bufStr)
    {
        someInfo = getOneTLE(bufStr);
        strcpy(someInfo.TLEI.name,"noname");
        str1 = someInfo.TLEstr1;
        str2 = someInfo.TLEstr2;
        someInfo.Type = TLEInfo;
        if(FileOperations::IsFirstLineValid(str1) && FileOperations::IsSecondLineValid(str2))
        {
                resInfo.append(someInfo);
        }
        bufStr = getNextTLE(bufStr);
    }
    return resInfo;
}
