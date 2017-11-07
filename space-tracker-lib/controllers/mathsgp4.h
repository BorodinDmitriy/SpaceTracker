#ifndef MATHSGP4_H
#define MATHSGP4_H

#include <QDateTime>
#include <QPoint>
#include <QString>

#include "information.h"

#include "SGP4.h"


namespace MathSgp4 {
QPointF getCoordinants(const QString &lineOne, const QString &lineTwo, const QDateTime &dt);
double getAltitude(const QString &lineOne, const QString &lineTwo, const QDateTime &dt);
FormTLE getForm(const QString &lineOne, const QString &lineTwo, const QDateTime &dt);
}

#endif // MATHSGP4_H
