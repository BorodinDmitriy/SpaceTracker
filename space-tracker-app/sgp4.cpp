#include "sgp4.h"

namespace Helpers {
DateTime fromQDateTime(const QDateTime &dt)
{
    return {
        dt.date().year(), dt.date().month(), dt.date().day(),
        dt.time().hour(), dt.time().minute(), dt.time().second()
    };
}

Eci findCurrentPositionEci(const QString &lineOne, const QString &lineTwo, const QDateTime &dt)
{
    SGP4 orbitalElement(Tle(lineOne.toStdString(), lineTwo.toStdString()));

    return orbitalElement.FindPosition(Helpers::fromQDateTime(dt));
}
}

MathSGP4::MathSGP4()
{

}

MathSGP4::~MathSGP4()
{

}

FormTLE MathSGP4::getForm(const std::__cxx11::string &str1, const std::__cxx11::string &str2, const QDateTime &dt)
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

double MathSGP4::getAltitude(const std::__cxx11::string &str1, const std::__cxx11::string &str2, const QDateTime &dt)
{
    return Helpers::findCurrentPositionEci(lineOne, lineTwo, dt).ToGeodetic().altitude;
}

QPointF MathSGP4::getCoorditants(const std::__cxx11::string &str1, const std::__cxx11::string &str2, const QDateTime &dt)
{
    auto geoPos = Helpers::findCurrentPositionEci(lineOne, lineTwo, dt).ToGeodetic();

    return {
        geoPos.longitude, geoPos.latitude
    };
}
