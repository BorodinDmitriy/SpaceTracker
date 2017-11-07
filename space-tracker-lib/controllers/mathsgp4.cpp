#include "mathsgp4.h"

namespace MathSgp4 {
namespace Helpers {
static DateTime fromQDateTime(const QDateTime &dt)
{
    return {
        dt.date().year(), dt.date().month(), dt.date().day(),
        dt.time().hour(), dt.time().minute(), dt.time().second()
    };
}

static Eci findCurrentPositionEci(const QString &lineOne, const QString &lineTwo, const QDateTime &dt)
{
    SGP4 orbitalElement(Tle(lineOne.toStdString(), lineTwo.toStdString()));

    return orbitalElement.FindPosition(Helpers::fromQDateTime(dt));
}
}
}


QPointF MathSgp4::getCoordinants(const QString &lineOne, const QString &lineTwo, const QDateTime &dt)
{
    auto geoPos = Helpers::findCurrentPositionEci(lineOne, lineTwo, dt).ToGeodetic();

    return {
        geoPos.longitude, geoPos.latitude
    };
}

double MathSgp4::getAltitude(const QString &lineOne, const QString &lineTwo, const QDateTime &dt)
{
    return Helpers::findCurrentPositionEci(lineOne, lineTwo, dt).ToGeodetic().altitude;
}

FormTLE MathSgp4::getForm(const QString &lineOne, const QString &lineTwo, const QDateTime &dt)
{
    auto curPos = Helpers::findCurrentPositionEci(lineOne, lineTwo, dt);
    auto geoPos = curPos.ToGeodetic();

    return {
        geoPos.longitude,
        geoPos.latitude,
        geoPos.altitude,
        curPos.Velocity().Magnitude()
    };
}
