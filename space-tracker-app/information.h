#ifndef INFORMATION_H
#define INFORMATION_H

#include <string>
#include <QPoint>

#define FILENAME "file"

enum TypeInfo{SSRInfo,TLEInfo};
enum TypeDataView{Map,Table};
enum SortType{Ascending,Descending};

struct Date
{
    char Day;
    char Mounth;
    int Year;
};

struct SSR
{

};

struct TLE
{
    char name[25];              //1
    int nor_id;                 //2
    char cl;                    //3
    char i_n_s[2];              //4
    int i_n_n;                  //5
    char i_n_p[3];              //6
    char era[2];                //7
    double era_t;               //8
    double der;                 //9
    double der2;                //10
    double b;                   //11
    char efi;                   //12
    int num;                    //13
    char sum;                   //14
    double incl;                //3
    double lg;                  //4
    double ex;                  //5
    double arg_per;             //6
    double aver_anom;           //7
    double freq;                //8
    unsigned long int era_num;  //9
    char sum_2;                 //10
};

struct Information
{
    enum TypeInfo Type;
    union
    {
        struct SSR SSRI;
        struct TLE TLEI;
    };
    std::string TLEstr1;
    std::string TLEstr2;
};

struct MemoryStruct
{
    char * memory;
    size_t size;
};

struct FormTLE
{
    double lastLongitude;
    double lastLatitude;
    double lastHeight;
    double lastSpeed;
};

#endif // INFORMATION_H
