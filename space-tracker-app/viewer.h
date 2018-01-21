#ifndef VIEWER_H
#define VIEWER_H

#include <QList>
#include <QPoint>
#include <QException>
#include <QMessageBox>

#include "draw.h"
#include "information.h"
#include "exceptions.h"

#define areaX 3
#define areaY 3

class Viewer
{
    public:
        Viewer();
        Viewer(Draw *drawOfMainControll);
        void drawTrace(QColor color);
        void drawTrace();
        bool checkTrace(const int x, const int y);
        void setListPoint(QList<QPoint> *newListPoint);
        void addToTable(int noradID, char *name, char typeObject, char *typeOrbit, char *ogp);
        void deleteFromTable(const int row);
        void addItemList(QPoint newItem);
        int getX(const int x);
        int getY(const int y);
    private:
        Draw *draw;
        QList<QPoint> *listOfPoint;
        QList<QPoint> getListPoint();
        QColor color;
};

#endif // VIEWER_H
