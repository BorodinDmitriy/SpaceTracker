#ifndef INFORMATION_H
#define INFORMATION_H

#include <string>
#include <QPoint>

#include "config.h"

enum TypeInfo{SSRInfo,TLEInfo};
enum TypeDataView{Map,Table};
enum SortType{Ascending,Descending};

struct Date
{
    char Day;
    char Mounth;
    int Year;
};

// TLE - Two-line element set, full information https://en.wikipedia.org/wiki/Two-line_element_set
struct TLE
{
    char name[25];              // Имя спутника
    int nor_id;                 // NORAD_ID - идентификационный номер спутника
    char cl;                    // Classifcation - Классификация спутника
    char i_n_s[2];              // Последние две цифры года запуска
    int i_n_n;                  // Номер запуска в году запуска
    char i_n_p[3];              // Вид запуска
    char era[2];                // Epoch отправная точка для расчетов (последние две цифры года)
    double era_t;               // Epoch time - время дня в году
    double der;                 // Время первой производной орбитального резонанса (Mean Motion)
    double der2;                // Время второй производной орбитального резонанса (Mean Motion)
    double b;                   // Переменная описания потока (число)
    char efi;                   // Тип эфемериды
    int num;                    // Значение, инкрементирующеся при создании новой tle с заданными параметрами
    char sum;                   // КОнтрольная сумма (по модулю 10)
    double incl;                // Наклон
    double lg;                  // Отклонение вправо
    double ex;                  // Эксцентриситет
    double arg_per;             // Аргумент наиболее дальней точки объекта
    double aver_anom;           // Mean anomaly (среднее)
    double freq;                // Частота вращения
    unsigned long int era_num;  // Число вращений в заданную эпоху
    char sum_2;                 // Контрольная сумма (по модулю 10)
};

struct Information
{
    enum TypeInfo Type;
    struct TLE TLEI;
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
