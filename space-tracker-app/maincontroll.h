#ifndef MAINCONTROLL_H
#define MAINCONTROLL_H

#include <QList>
#include <QMessageBox>
#include <QException>
#include <string>
#include <QDateTime>
#include <stdlib.h>

#include "controller.h"
#include "information.h"
#include "sgp4.h"

class Draw;
class Loader;

class MainControll
{
    public:
        MainControll();
        MainControll(void *fieldOfMap, void *fieldOfTextInformatio);
        ~MainControll();
        void loadTLEforDB(std::string FileName);
        void loadTLEforDBInter();
        void setupDate(const QDateTime newDateTime);
        QDateTime getDate();
        void sort(const int column, const Qt::SortOrder order);
        FormTLE *selectObjectOnMap(const int indexRow);
        FormTLE *selectObjectOnTable(const int x, const int y);
        void drawAllTrace();
        void drawMap();
        void revertMap();
        void clearMap();
    private:
        QList <Controller> *controllers;
        MathSGP4 *sgp4;
        Loader *loader;
        QDateTime *time;
        Draw *draw;

        void setupSetting();
        void insertData(const QList<Information> listOfData, QDateTime dateTime);
        FormTLE getTLE(const int noradID);
};

#endif // MAINCONTROLL_H
