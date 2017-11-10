#ifndef CONTROLLERSPACEOBJECT_H
#define CONTROLLERSPACEOBJECT_H

#include <QObject>
#include <QUuid>

class ControllerSpaceObject : public QObject
{
    Q_OBJECT
public:
    explicit ControllerSpaceObject(QObject *parent = 0);

signals:


public slots:
    void drawMap(bool clear = false);
    void drawAllTraces();
    void drawSelectedTraces();
    void selectObjectByUID(const QUuid &uid);
    void selectObjectByCoords(const QPoint &coords);


private:
    Model *model;

};

#endif // CONTROLLERSPACEOBJECT_H
