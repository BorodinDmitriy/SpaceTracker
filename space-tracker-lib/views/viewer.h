#ifndef VIEWER_H
#define VIEWER_H

#include <QObject>
#include "views/drawer.h"
#include "models/model.h"

class Viewer : public QObject
{
    Q_OBJECT
public:
    explicit Viewer(int width, int height, QObject *parent = nullptr);
    ~Viewer();

signals:
    void imageUpdate(QPixmap pixmap);

public slots:
    void drawObjects(const QVector<Model*> &objects);
    void selectObject(const Model &object);

private:
    Drawer *drawer;
};

#endif // VIEWER_H
