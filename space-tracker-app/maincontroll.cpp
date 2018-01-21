#include "maincontroll.h"

// Create component for MainControll
MainControll::MainControll()
{
    sgp4 = new class MathSGP4();
    loader = new class Loader();
    controllers = new class QList<class Controller>();
    time = new class QDateTime();
    draw = NULL;
    setupSetting();
}

MainControll::MainControll(void *fieldOfMap, void *fieldOfTextInformatio)
{
    sgp4 = new class MathSGP4();
    loader = new class Loader();
    controllers = new class QList<class Controller>();
    time = new QDateTime();
    draw = new class Draw(fieldOfMap, fieldOfTextInformatio);
    setupSetting();
}

// Destroy component for MainControll
MainControll::~MainControll()
{
    delete sgp4;
    delete loader;
    delete controllers;
    delete time;
}

    /*Private methods*/

// Start setup DateTime
void MainControll::setupSetting()
{
    time->setTime(QTime::currentTime());
    time->setDate(QDate::currentDate());
    return;
}

// Add TLE in program
void MainControll::insertData(const QList<struct Information> listOfData, QDateTime dateTime)
{
    try
    {
        if (controllers == NULL)
            throw NullPointer();
        if (controllers->empty())
        {
            class Controller *item = NULL;
            for (int i = 0; i < listOfData.count(); i++)
            {
                item = new class Controller(sgp4, draw);
                if (item == NULL)
                    throw MemoryAllocationError();
                item->addInformation(listOfData[i], *time);
                (*controllers).append(*item);
                if (time == NULL)
                    throw MemoryAllocationError();
                (*controllers)[i].addInformationOnTable(*time);
            }
        }
        else
        {
            class Controller *item = NULL;
            int noradID;
            bool state;
            int index;
            for(int j = 0; j < listOfData.count(); j++)
            {
                state = false;
                if (listOfData[j].Type == TLEInfo)
                    noradID = listOfData[j].TLEI.nor_id;
                for(int i = 0; i < controllers->count(); i++)
                {
                    if (noradID == (*controllers)[i].getNoradID())
                    {
                        state = (*controllers)[i].addInformation(listOfData[j], *time);
                        break;
                    }
                }
                if (state == false)
                {
                    item = new class Controller(sgp4, draw);
                    if (item == NULL)
                        throw MemoryAllocationError();
                    item->addInformation(listOfData[j], dateTime);
                    controllers->append(*item);
                    index = controllers->count();
                    (*controllers)[index].addInformationOnTable(*time);
                }
            }
        }
    }
    catch(BaseException &error)
    {
        QMessageBox helper;
        helper.critical(NULL, "Error", error.what());
    }
    return;
}

    /*Public methods*/

// Load TLE for DataBase
void MainControll::loadTLEforDB(std::string FileName)
{
    try
    {
        if (loader == NULL)
            throw NullPointer();
        struct Date currentDate;
        QList<struct Information> listLoadTLE;
        listLoadTLE = loader->loadFileTLE(currentDate, FileName);
        if (listLoadTLE.empty())
            return;
        QDateTime dateTime;
        QDate date;
        date.setDate(currentDate.Year, currentDate.Mounth, currentDate.Day);
        dateTime.setDate(date);
        insertData(listLoadTLE, dateTime);
    }
    catch(QException &error)
    {
        QMessageBox helper;
        helper.critical(NULL, "Error", error.what());
    }
    return;
}

void MainControll::sort(const int column, const Qt::SortOrder order)
{
    draw->sortTableInfrormation(column, order);
    return;
}

struct FormTLE *MainControll::selectObjectOnMap(const int indexRow)
{
    int noradID;
    noradID = draw->getNoradID(indexRow);
    for (int i = 0; i < controllers->count(); i++)
    {
        if ((*controllers)[i].getNoradID() == noradID)
        {
            (*controllers)[i].showTrace();
            break;
        }
    }
    if (noradID != NULL)
    {
        struct FormTLE information = (getTLE(noradID));
        return (&information);
    }
    return NULL;
}

struct FormTLE *MainControll::selectObjectOnTable(const int x, const int y)
{
    int noradID = -1;
    for (int i = 0; i < controllers->count(); i++)
    {
        noradID = (*controllers)[i].checkTrace(x, y);
        if (noradID != -1)
            break;
    }
    if ( noradID == -1)
        return NULL;
    draw->selectObjectOnTable(noradID);
    if(noradID != NULL)
    {
        struct FormTLE information = getTLE(noradID);
        return (&information);
    }
    return NULL;
}

void MainControll::setupDate(const QDateTime newDateTime)
{
    (*time) = newDateTime;
    return;
}

QDateTime MainControll::getDate()
{
    return *time;
}

struct FormTLE MainControll::getTLE(const int noradID)
{
    try
    {
        if (controllers == NULL)
            throw NullPointer();
        for (int i = 0; i < controllers->count(); i++)
        {
            if ((*controllers)[i].getNoradID() == noradID)
            {
                return (*controllers)[i].getFormTLE(*time);
            }
        }
        struct FormTLE errorTLE = {0,0,0,0};
        return errorTLE;
    }
    catch (BaseException &error)
    {
        QMessageBox helper;
        helper.critical(NULL, "Error", error.what());
    }
}

void MainControll::drawMap()
{
    draw->drawMap();
    return;
}

void MainControll::revertMap()
{
    draw->revert();
    return;
}

void MainControll::drawAllTrace()
{
    try
    {
        for (int i = 0; i < controllers->count(); i++)
        {
            (*controllers)[i].showTraces();
        }
    }
    catch (BaseException &error)
    {
        QMessageBox helper;
        helper.critical(NULL, "Error", error.what());
    }
}

void MainControll::clearMap()
{
    draw->clearMap();
}

void MainControll::loadTLEforDBInter()
{
    try
    {
        if (loader == NULL)
            throw NullPointer();
        struct Date currentDate;
        QList<struct Information> listLoadTLE;
        listLoadTLE = loader->loadAllTLE(currentDate);
        if (listLoadTLE.empty())
            return;
        QDateTime dateTime;
        QDate date;
        date.setDate(currentDate.Year, currentDate.Mounth, currentDate.Day);
        dateTime.setDate(date);
        insertData(listLoadTLE, dateTime);
    }
    catch(QException &error)
    {
        QMessageBox helper;
        helper.critical(NULL, "Error", error.what());
    }
    return;
}
