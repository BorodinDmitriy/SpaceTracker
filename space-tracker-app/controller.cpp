#include "controller.h"

Controller::Controller(MathSGP4 *linkSGP, void *fieldDraw):
    model(new Model()),
    viewer(new Viewer(fieldDraw)),
    sgp(linkSGP)
{

}

Controller::~Controller()
{
    delete model;
    delete viewer;
}

int Controller::getNoradID()
{
    if (model == NULL)
        return -1;
    return model->getNoradID();
}

bool Controller::addInformation(const Information newItem, QDateTime dateTime)
{
    if (model == NULL)
        return false;
    bool state = model->addInformation(newItem);
    if (state == false)
        return state;
    if(newItem.Type == TLEInfo)
    {
        QPoint itemForTrace = sgp->getCoorditants(newItem.TLEstr1, newItem.TLEstr2, dateTime);
        viewer->addItemList(itemForTrace);
    }
    return state;
}

int Controller::checkTrace(const int x, const int y)
{
    if (viewer == NULL)
        return -1;
    bool flag = viewer->checkTrace(x,y);
    if (flag == true)
        return model->getNoradID();
    return -1;
}

void Controller::showTrace()
{
    if (viewer == NULL)
        return;
    viewer->drawTrace(QColor(255,51,0));
    return;
}

void Controller::showTraces()
{
    if (viewer == NULL)
        return;
    viewer->drawTrace();
    return;
}

struct FormTLE Controller::getFormTLE(QDateTime dateTime)
{
    std::string str1;
    std::string str2;
    bool state = model->getStringInformation(&str1, &str2);
    if (state == false)
        return FormTLE{0,0,0,0};
    return sgp->getForm(str1, str2, dateTime);
}

void Controller::addInformationOnTable(QDateTime dateTime)
{
    int noradID = model->getNoradID();
    char *name = model->getName();
    char typeObject = model->getTypeObject();
    char *typeOrbit = getTypeOrbit(dateTime);
    char *ogp = model->getOGP();
    if (noradID < 0 || name == NULL || typeOrbit == NULL || ogp == NULL )
        return;
    viewer->addToTable(noradID, name, typeObject, typeOrbit, ogp);
    return;
}

char *Controller::getTypeOrbit(QDateTime dateTime)
{
    std::string str1;
    std::string str2;
    bool state = model->getStringInformation(&str1, &str2);
    if (state == false)
        return NULL;
    double altitude = sgp->getAltitude(str1, str2, dateTime);
    if (altitude >= 300 && altitude <= 600)
        return "ННО";
    double angle = model->getAngle();
    if (angle >= 88 && angle <= 92)
        return "CCO";
    double period = model->getPeriod();
    double angularity = (2*nPI) / period;
    double diffAngular = fabs(angularity - angularVelocityEarth);
    if (altitude >= gsoAltitude - 10 && altitude <= gsoAltitude + 10 && diffAngular < 1)
        return "ГСО";
    return "Не определено";
}
