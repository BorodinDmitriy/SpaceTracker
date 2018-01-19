#include "loader.h"

Loader::Loader()
{
        win = 0;
        bd = 0;
        pars = 0;
        try
        {
            win = new WebInter();
        }
        catch (BaseException &error)
        {
            win = 0;
            QMessageBox helper;
            helper.critical(NULL, "Error: Loader", error.what());
        }
        try
        {
            bd = new DBInter();
        }
        catch (BaseException &error)
        {
            bd = 0;
            QMessageBox helper;
            helper.critical(NULL, "Error: Loader", error.what());
        }
        try
        {
            pars = new TleParser();
        }
        catch (BaseException &error)
        {
            bd = 0;
            QMessageBox helper;
            helper.critical(NULL, "Error: Loader", error.what());
        }
    return;
}

Loader::~Loader()
{
    try
    {
        delete win;
        delete bd;
    }
    catch (BaseException &error)
    {
        QMessageBox helper;
        helper.critical(NULL, "Error: Loader", error.what());
    }
}

QList<Information> Loader::loadAllTLE(const Date &dt)
{
    QList<Information> resInfo;
    if (bd == 0)
        return resInfo;
    resInfo = bd->loadAllTLE(dt);
    if (resInfo.empty())
    {
        if (win == 0)
            return resInfo;
        resInfo = win->loadAllTLE(dt);
        bd->addTLE(resInfo, dt);
    }
    return resInfo;
}

QList<Information> Loader::loadFileTLE(const Date &dt, std::string fn)
{
    QList<Information> resInfo;
    std::ifstream file(fn.c_str());
    std::string result;
    if (file.good())
    {
        std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::back_inserter(result));
        resInfo = pars->getTLE(result.c_str());
        return resInfo;
    }
    else
        throw FileExistError();
    return resInfo;
}

QList<Information> Loader::loadAllSSR(const Date &)
{
    QList<Information> resInfo;
    return resInfo;
}

QList<Information> Loader::loadTLE(const unsigned long &id, const Date &dt)
{
    QList<Information> resInfo;
    QList<Information> bufResInfo;
    if (bd == 0)
        return resInfo;
    resInfo = bd->loadTLE(id, dt);
    if (resInfo.empty())
    {
        bufResInfo = win->loadTLE(id, dt);
        bd->addTLE(bufResInfo, dt);
    }
    QList<Information>::iterator i;
    for (i = bufResInfo.begin(); i != bufResInfo.end(); ++i)
    {
        resInfo.append(*i);
    }
    return resInfo;
}

QList<Information> Loader::loadSSR(const unsigned long&  id, const Date&)
{
    QList<Information> resInfo;
    return resInfo;
}
