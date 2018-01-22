#ifndef DBINTER_H
#define DBINTER_H

#include <iostream>
#include <QList>
#include <string>
#include <sstream>
#include <iomanip>
#include <QDate>
#include <QMessageBox>

#include "exceptions.h"
#include "sqlite3/sqlite3.h"
#include "information.h"

#include "config.h"


/*struct TLE
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
};*/

class DBInsertQuery {
public:
    std::string query;
    DBInsertQuery();
    void addLineBreak();
    void addCloseBrackets();
    std::string getQuery();
    template<typename T>
    void addParameter(T parameter);
    template<typename T>
    void addPrecisedParameter(T parameter);
    template<typename T>
    void addParameterArray(T parameterArray);
};

class DBInter
{
    public:
        DBInter();
        ~DBInter();
        QList<Information> loadAllTLE(const Date &dt);
        QList<Information> loadTLE(const unsigned long &id, const Date &dt);
        void addTLE(QList<Information> data, const Date &date);
        void addTLE(TLE tl, const Date &dt);
    private:
        sqlite3* db;
};

#endif // DBINTER_H
