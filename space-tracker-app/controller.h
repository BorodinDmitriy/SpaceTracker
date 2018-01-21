#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QList>
#include <QPoint>
#include <QDateTime>

#include "constants.h"
#include "sgp4.h"

// Заглушка.
class Model;
class Viewer;

class Controller
{
public:
    Controller(MathSGP4 *linkSGP, void *fieldDraw);
    ~Controller();
    bool addInformation(const Information newItem, QDateTime dateTime);
    void addInformationOnTable(QDateTime dateTime);
    int getNoradID();
    int checkTrace(const int x, const int y);
    void showTrace();
    void showTraces();
    struct FormTLE getFormTLE(QDateTime dateTime);
private:
    Model *model;
    Viewer *viewer;
    MathSGP4 *sgp;
    char *getTypeOrbit(QDateTime dateTime);
};

#endif // CONTROLLER_H
