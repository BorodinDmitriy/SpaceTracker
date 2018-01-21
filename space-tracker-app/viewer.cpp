#include "viewer.h"

Viewer::Viewer()
{
    try
    {
        listOfPoint = NULL;
        listOfPoint = new QList<QPoint>();
        if (listOfPoint == NULL)
            throw MemoryAllocationError();
    }
    catch (BaseException &error)
    {
        QMessageBox helper;
        helper.critical(NULL, "Error: Viewer", error.what());
    }
    return;
}

Viewer::Viewer(Draw *drawOfMainControll)
{
    try
    {
        listOfPoint = NULL;
        draw = NULL;
        listOfPoint = new QList<QPoint>();
        draw = drawOfMainControll;
        color = QColor(rand() % 255, rand() % 255, rand() % 255);
        if (listOfPoint == NULL)
            throw MemoryAllocationError();
    }
    catch (BaseException &error)
    {
        QMessageBox helper;
        helper.critical(NULL, "Error: Viewer", error.what());
    }
    return;
}

bool Viewer::checkTrace(const int x, const int y)
{
    int m = listOfPoint->count();
    int traceX;
    int traceY;
    for (int i = 0; i < m; i++)
    {
        traceX = getX((*listOfPoint)[i].x());
        traceY = getY((*listOfPoint)[i].y());
        if ((traceX <= x + areaX) && (traceX >= x - areaX) && (traceY <= y + areaY) && (traceY >= y - areaY))
            return true;
    }
    return false;
}

void Viewer::drawTrace(QColor color)
{
    draw->drawTrace(getListPoint(), color);
    return;
}

void Viewer::drawTrace()
{
    draw->drawTrace(getListPoint(), color);
    return;
}

QList<QPoint> Viewer::getListPoint()
{
    return *listOfPoint;
}

void Viewer::setListPoint(QList<QPoint> *newListPoint)
{
    listOfPoint = newListPoint;
}

void Viewer::addToTable(int noradID, char *name, char typeObject, char *typeOrbit, char *ogp)
{
    draw->addToTable(noradID, name, typeObject, typeOrbit, ogp);
    return;
}

void Viewer::deleteFromTable(const int row)
{
    draw->deleteFromTable(row);
    return;
}

void Viewer::addItemList(QPoint newItem)
{
    (*listOfPoint).append(newItem);
    return;
}

int Viewer::getX(const int x)
{
    double scaleX;
    double scaleY;
    draw->getScale(&scaleX, &scaleY);
    if ( x > longitude)
        return (x - longitude) * scaleX;
    else
        return (x + longitude) * scaleX;
}

int Viewer::getY(const int y)
{
    double scaleX;
    double scaleY;
    draw->getScale(&scaleX, &scaleY);
    return ( -y + latitude) * scaleY;
}
