#include "loader.h"

Loader::Loader()
{
        bd = 0;
        pars = 0;
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
    delete bd;
}

QList<Information> Loader::loadAllTLE(const Date &dt)
{
    QList<Information> resInfo;
    if (bd == 0)
        return resInfo;
    resInfo = bd->loadAllTLE(dt);
    if (resInfo.empty())
    {
        resInfo = WebInterSingleton::Instance().loadAllTLE(dt);
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


QList<Information> Loader::loadTLE(const unsigned long &id, const Date &dt)
{
    QList<Information> resInfo;
    QList<Information> bufResInfo;
    if (bd == 0)
        return resInfo;
    resInfo = bd->loadTLE(id, dt);
    if (resInfo.empty())
    {
        bufResInfo = WebInterSingleton::Instance().loadTLE(id, dt);
        bd->addTLE(bufResInfo, dt);
    }
    QList<Information>::iterator i;
    for (auto __begin = bufResInfo.begin(), __end = bufResInfo.end(); __begin != __end; ++__begin) {
        resInfo.append(*__begin);
    }
    return resInfo;
}
