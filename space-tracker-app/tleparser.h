#ifndef TLEPARSER_H
#define TLEPARSER_H

#include <QList>
#include <string>
#include <iostream>

#include "information.h"
#include "exceptions.h"
#include "fileoperations.h"

class TleParser
{
    public:
        TleParser();
        Information getOneTLE(const char *str);
        const char *getNextTLE(const char *str);
        QList<struct Information> getTLE(const char *str);
    private:
        void firstStrPars(const char *str, Information &tl);
        void secondStrPars(const char *str, Information &tlIn);
        void thirdStrPars(const char *str, Information &tlIn);
        void setName(const char *str, TLE &tl); //1
        void setID(const char *str, TLE &tl);  //2
        void setClass(const char *str, TLE &tl); //3
        void setINS(const char *str, TLE &tl);  //4
        void setINN(const char *str, TLE &tl);  //5
        void setINP(const char *str, TLE &tl); //6
        void setEra(const char *str, TLE &tl); //7
        void setEraT(const char *str, TLE &tl); //8
        void setDer(const char *str, TLE &tl);  //9
        void setDer2(const char *str, TLE &tl);  //10
        void setB(const char *str, TLE &tl);  //11
        void setEfi(const char *str, TLE &tl); //12
        void setNum(const char *str, TLE &tl);  //13
        void setSum(const char *str, TLE &tl);  //14
        void setIncl(const char *str, TLE &tl); //3
        void setLg(const char *str, TLE &tl);  //4
        void setEx(const char *str, TLE &tl);  //5
        void setArgPer(const char *str, TLE &tl);//6
        void setAverAnom(const char *str, TLE &tl);//7
        void setFreq(const char *str, TLE &tl);//8
        void setEraNum(const char *str, TLE &tl);//9
        void setSum2(const char *str, TLE &tl);//10
};

#endif // tleparser_H
