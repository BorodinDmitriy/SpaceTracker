#ifndef LOADER_H
#define LOADER_H

#include <QList>
#include <iostream>
#include <string>
#include <QMessageBox>

#include "exceptions.h"
#include "webinter.h"
#include "dbinter.h"
#include "tleparser.h"
#include "fstream"
#include "information.h"
#include "webintersingleton.h"

class Loader
{
    public:
        Loader();
        ~Loader();
        QList<Information> loadAllTLE(const Date &dt);
        QList<Information> loadFileTLE(const Date &dt, std::string fn);
        QList<Information> loadTLE(const unsigned long &id, const Date &dt);
    private:
       //WebInterSingleton &win;
       DBInter *bd;
       TleParser *pars;
};
#endif // LOADER_H
