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
    for (int i = buffer->count() - 1; i >= 0; i--)
    {
        if ((*buffer)[i].Type == TLEInfo)
        {
            (*str1) = (*buffer)[i].TLEstr1;
            (*str2) = (*buffer)[i].TLEstr2;
            return true;
        }
    }
    return false;
}

char *Model::getName()
{
    for(int i = buffer->count() - 1; i >= 0; i--)
    {
        if ((*buffer)[i].Type == TLEInfo)
        {
            return (*buffer)[i].TLEI.name;
        }
    }
    return "NONAME";
}

char Model::getTypeObject()
{
    for(int i = buffer->count() - 1; i >= 0; i--)
    {
        if ((*buffer)[i].Type == TLEInfo)
        {   
            return (*buffer)[i].TLEI.cl;
        }
    }
    return '\0';
}

double Model::getAngle()
{
    for(int i = buffer->count() - 1; i >= 0; i--)
    {
        if ((*buffer)[i].Type == TLEInfo)
        {
            return (*buffer)[i].TLEI.incl;
        }
    }
    return 0;
}

double Model::getPeriod()
{
    for(int i = buffer->count() - 1; i >= 0; i--)
    {
        if ((*buffer)[i].Type == TLEInfo)
        {
            return 1 / (*buffer)[i].TLEI.freq;
        }
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
