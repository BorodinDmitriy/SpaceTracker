#ifndef ORBITCONTROLLER_H
#define ORBITCONTROLLER_H

#include <QObject>


class OrbitController : public QObject
{
    Q_OBJECT

public:
    explicit OrbitController();

    virtual ~OrbitController();
};

#endif // ORBITCONTROLLER_H
