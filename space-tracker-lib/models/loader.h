#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <QDateTime>

class Loader
{
public:
    Loader();
    void getDataFromAPI(std::string url, QDateTime datetime);
    void getDataFromDB(QDateTime datetime);


private:
    void saveDataToDB(TLE *data);
    void updateDataInDB(TLE *data);

    Parser *parser;

};

#endif // LOADER_H
