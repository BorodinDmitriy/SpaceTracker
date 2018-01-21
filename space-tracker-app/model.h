#ifndef MODEL_H
#define MODEL_H

#include <stdlib.h>
#include <QList>
#include <QMessageBox>
#include <string>
#include <iostream>
#include <stdio.h>

#include "information.h"
#include "exceptions.h"

class Model
{
    public:
        Model();
        Model(int newNoradID);
        ~Model();
        bool addInformation(Information info);
        const int getNoradID();
        char *getName();
        char getTypeObject();
        double getPeriod();
        double getAngle();
        char *getOGP();
        QList<Information> *getList();
        bool getStringInformation(std::string *str1, std::string *str2);
        bool condition(QList<Information> buffer);
    private:        
        int noradID;
        QList<Information> *buffer;
};


#endif // MODEL_H
