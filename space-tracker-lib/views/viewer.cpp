#include "viewer.h"

Viewer::Viewer(int width, int height, QObject *parent) : QObject(parent)
{
    drawer = new Drawer(width, height);
}

Viewer::~Viewer()
{
    delete drawer;
}

void Viewer::drawObjects(const QVector<Model *> &objects)
{
    for (Model* object : objects)
        drawer->drawObject(object->getScreenCoords());
    emit imageUpdate(drawer->getImage());
}

void Viewer::selectObject(const Model &object)
{
    drawer->drawSelectedObject(object.getScreenCoords());
    emit imageUpdate(drawer->getImage());
}
