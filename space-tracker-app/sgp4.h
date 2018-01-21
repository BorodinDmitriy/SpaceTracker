#ifndef SGP4_H
#define SGP4_H

#include <iostream>
#include <QPoint>
#include <QList>
#include <string>
#include <QDateTime>
#include <QMessageBox>

#include "information.h"

#include "SGP4.h"

class MathSGP4
{
public:
    MathSGP4();
    ~MathSGP4();
    QPointF getCoorditants(const std::string &str1, const std::string &str2, const QDateTime &dt);
    double getAltitude(const std::string &str1, const std::string &str2, const QDateTime &dt);
    FormTLE getForm(const std::string &str1, const std::string &str2, const QDateTime &dt);
};

#endif // SGP4_H
