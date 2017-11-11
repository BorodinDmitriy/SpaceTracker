#ifndef DRAWER_H
#define DRAWER_H

#include <QPixmap>
#include <QImage>
#include <QPainter>

class Drawer
{
public:
    Drawer(int width, int height);

    void drawObject(const QPoint &point);
    void drawSelectedObject(const QPoint &point);

    QPixmap getImage();

private:
    int width;
    int height;

    QPixmap pixmap;
    QPainter painter;

    QImage background;
    QImage objectImage;

    const int objectRadius = 3;
};

#endif // DRAWER_H
