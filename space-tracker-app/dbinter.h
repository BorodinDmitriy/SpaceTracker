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

#define DirectoryDataBase "C:/BMSTU/PPO/TEST/build-untitled-Desktop-Debug/database/dbfile"

class DBInter
{
    public:
        DBInter();
        ~DBInter();
        QList<Information> loadAllTLE(const Date &dt);
        QList<Information> loadAllSSR(const Date &);
        QList<Information> loadSSR(const unsigned long &id, const Date &);
        QList<Information> loadTLE(const unsigned long &id, const Date &dt);
        void addTLE(QList<Information> data, const Date &date);
        void addSSR(QList<Information>, const Date &);
        void addTLE(TLE tl, const Date &dt);
        void addSSR(SSR, const Date &);
    private:
        sqlite3* db;
};

#endif // DBINTER_H
