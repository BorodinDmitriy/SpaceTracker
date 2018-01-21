#include "model.h"

Model::Model()
{
    noradID = -1;
    try
    {
        buffer = new QList<Information>();
        if (buffer == NULL)
            throw MemoryAllocationError();
    }
    catch (BaseException &error)
    {
        QMessageBox box;
        box.critical(0, "Error: Model", error.what());
    }
    return;
}

Model::Model(int newNoradID)
{
    noradID = newNoradID;
    try
    {
        buffer = new QList<Information>();
        if (buffer == NULL)
            throw MemoryAllocationError();
    }
    catch (BaseException &error)
    {
        QMessageBox box;
        box.critical(0, "Error: Model", error.what());
    }
    return;
}

Model::~Model()
{
    delete buffer;
    return;
}

bool Model::addInformation(Information info)
{
    (*buffer).append(info);
    if (noradID == -1)
        noradID = info.TLEI.nor_id;
    return true;
}

const int Model::getNoradID()
{
    return noradID;
}

bool Model::getStringInformation(std::string *str1, std::string *str2)
{
    QList<Information>::iterator iter = std::find_if((*buffer).begin(),(*buffer).end(), [] (const Information a) {
        return a.Type == TLEInfo;
    });

    if ((*iter).Type) {
        (*str1) = (*iter).TLEstr1;
        (*str2) = (*iter).TLEstr2;
        return true;
    }
    return false;
}

char *Model::getName()
{
    QList<Information>::iterator iter = std::find_if((*buffer).begin(),(*buffer).end(), [] (const Information a) {
        return a.Type == TLEInfo;
    });

    if ((*iter).Type) {
        return (*iter).TLEI.name;
    }
    return "NONAME";
}

char Model::getTypeObject()
{
    QList<Information>::iterator iter = std::find_if((*buffer).begin(),(*buffer).end(), [] (const Information a) {
        return a.Type == TLEInfo;
    });

    if ((*iter).Type) {
        return (*iter).TLEI.cl;
    }
    return '\0';
}

double Model::getAngle()
{
    QList<Information>::iterator iter = std::find_if((*buffer).begin(),(*buffer).end(), [] (const Information a) {
        return a.Type == TLEInfo;
    });

    if ((*iter).Type) {
        return (*iter).TLEI.incl;
    }
    return 0;
}

double Model::getPeriod()
{
    QList<Information>::iterator iter = std::find_if((*buffer).begin(),(*buffer).end(), [] (const Information a) {
        return a.Type == TLEInfo;
    });

    if ((*iter).Type) {
        return 1 / (*iter).TLEI.freq;;
    }
    return 0;
}

char *Model::getOGP()
{
    return "country";
}

QList<Information> *Model::getList()
{
    return buffer;
}
