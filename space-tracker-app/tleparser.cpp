#include "tleparser.h"
#include "config.h"

TleParser::TleParser()
{

}

std::string TleParser::formParsingNumberString(const char *str, int startPosition, int finishPosition) {
    std::string buf;
    for (int i = startPosition; i < finishPosition; i++)
    {
        buf += str[i];
    }
    return buf;
}

std::string TleParser::formParsingTextString(const char *str, int startPosition, int finishPosition) {
    std::string buf;
    for (int i = startPosition; i < finishPosition; i++)
    {
        if (((str[i] == '+') || (str[i] == '-')) && (!buf.empty()))
        {
            buf += 'E';
        }
        buf += str[i];
    }
    return buf;
}

std::string TleParser::processFloatString(std::string &str) {
    std::string buf = str;
    if (((buf[0] == '+') || (buf[0] == '-')))
    {
        buf.insert(1, ".");
    }
    else
    {
        buf.insert(0, ".");
    }
    return buf;
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
    strncpy(tl.name, buf.c_str(), buf.size() - 1);
    tl.name[i] = '\0';
    return;
}//1

void TleParser::setID(const char *str, TLE &tl)
{
    tl.nor_id = atoi(formParsingNumberString(str,TLE_ID_START_POSITION,TLE_ID_FINISH_POSITION).c_str());
    return;
}  //2

void TleParser::setClass(const char *str, TLE &tl)
{
    tl.cl = str[TLE_CLASSIFICATION_START_AND_FINISH_POSITION];
    return;
} //3

void TleParser::setINS(const char *str, TLE &tl)
{
    std::string buf = formParsingNumberString(str,TLE_LAUNCH_YEAR_START_POSITION,TLE_LAUNCH_YEAR_FINISH_POSITION);
    strncpy(tl.i_n_s, buf.c_str(), buf.size() - 1);
    return;
}  //4

void TleParser::setINN(const char *str, TLE &tl)
{
    tl.i_n_n = atoi(formParsingNumberString(str,TLE_LAUNCH_DATA_START_POSITION, TLE_LAUNCH_DATA_FINISH_POSITION).c_str());
    return;
}  //5

void TleParser::setINP(const char *str, TLE &tl)
{
    std::string buf = formParsingNumberString(str,TLE_LAUNCH_TYPE_START_POSITION,TLE_LAUNCH_TYPE_FINISH_POSITION);
    strncpy(tl.i_n_p, buf.c_str(), buf.size() - 1);
    return;
} //6

void TleParser::setEra(const char *str, TLE &tl)
{
    std::string buf = formParsingNumberString(str,TLE_ERA_START_POSITION,TLE_ERA_FINISH_POSITION);
    strncpy(tl.era, buf.c_str(), buf.size() - 1);
    return;
} //7

void TleParser::setEraT(const char *str, TLE &tl)
{
    tl.era_t = std::strtod(formParsingTextString(str,TLE_ERA_TYPE_START_POSITION,TLE_ERA_TYPE_FINISH_POSITION).c_str(), 0);
    return;
} //8

void TleParser::setDer(const char *str, TLE &tl)
{
    tl.der = std::strtod(formParsingTextString(str,TLE_FIRST_DERIVATIVE_START_POSITION,TLE_FIRST_DERIVATIVE_FINISH_POSITION).c_str(), 0);
    return;
}  //9

void TleParser::setDer2(const char *str, TLE &tl)
{
    std::string buf = formParsingTextString(str,TLE_SECOND_DERIVATIVE_START_POSITION,TLE_SECOND_DERIVATIVE_FINISH_POSITION);
    tl.der2 = std::strtod(processFloatString(buf).c_str(), 0);
    return;
}  //10

void TleParser::setB(const char *str, TLE &tl)
{
    std::string buf = formParsingTextString(str,TLE_FLOW_TYPE_START_POSITION,TLE_FLOW_TYPE_FINISH_POSITION);
    tl.b = std::strtod(processFloatString(buf).c_str(), 0);
    return;
}  //11

void TleParser::setEfi(const char *str, TLE &tl)
{
    tl.efi = 0;
    return;
} //12

void TleParser::setNum(const char *str, TLE &tl)
{
    tl.num = atoi(formParsingNumberString(str,TLE_NUM_TYPE_START_POSITION,TLE_NUM_TYPE_FINISH_POSITION).c_str());
    return;
}  //13

void TleParser::setSum(const char *str, TLE &tl)
{
    tl.sum = str[TLE_CHECK_SUM_START_AND_FINISH_POSITION] - (int)'0';
    return;
}  //14

void TleParser::setIncl(const char *str, TLE &tl)
{
    tl.incl = std::strtod(formParsingTextString(str,TLE_INCLINATION_START_POSITION,TLE_INCLINATION_FINISH_POSITION).c_str(), 0);
    return;
} //3

void TleParser::setLg(const char *str, TLE &tl)
{
    tl.lg = std::strtod(formParsingTextString(str,TLE_INCLINATION_TO_THE_RIGHT_START_POSITION,TLE_INCLINATION_TO_THE_RIGHT_FINISH_POSITION).c_str(), 0);
    return;
}  //4

void TleParser::setEx(const char *str, TLE &tl)
{
    std::string buf = formParsingTextString(str,TLE_EXCENTRICITY_START_POSITION,TLE_EXCENTRICITY_FINISH_POSITION);
    tl.ex = std::strtod(processFloatString(buf).c_str(), 0);
    return;
}  //5

void TleParser::setArgPer(const char *str, TLE &tl)
{
    tl.arg_per = std::strtod(formParsingTextString(str,TLE_PERIGEE_START_POSITION,TLE_PERIGEE_FINISH_POSITION).c_str(), 0);
    return;
}//6

void TleParser::setAverAnom(const char *str, TLE &tl)
{
     tl.aver_anom = std::strtod(formParsingTextString(str,TLE_MEAN_ANOMALY_START_POSITION,TLE_MEAN_ANOMALY_FINISH_POSITION).c_str(), 0);
     return;
}//7

void TleParser::setFreq(const char *str, TLE &tl)
{
    tl.freq = std::strtod(formParsingTextString(str,TLE_MEAN_ANOMALY_START_POSITION,TLE_MEAN_ANOMALY_FINISH_POSITION).c_str(), 0);
    return;
}//8

void TleParser::setEraNum(const char *str, TLE &tl)
{
    tl.era_num = atoi(formParsingNumberString(str,TLE_ERA_NUM_START_POSITION,TLE_ERA_NUM_START_POSITION).c_str());
    return;
}//9

void TleParser::setSum2(const char *str, TLE &tl)
{
    tl.sum_2 = str[TLE_CHECK_SUM_START_AND_FINISH_POSITION];
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
