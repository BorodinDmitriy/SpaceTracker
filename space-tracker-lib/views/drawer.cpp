#include "drawer.h"

Drawer::Drawer(int width, int height) : pixmap(width, height)
{
    painter.initFrom(&pixmap);
}

void Drawer::drawObject(const QPoint &point)
{
    painter.setPen(Qt::green);
    painter.drawEllipse(point, objectRadius, objectRadius);
}

void Drawer::drawSelectedObject(const QPoint &point)
{
    painter.setPen(Qt::green);
    painter.drawEllipse(point, objectRadius, objectRadius);
    painter.setPen(Qt::red);
    painter.drawEllipse(point, 2 * objectRadius, 2 * objectRadius);
}

QPixmap Drawer::getImage()
{
    return pixmap;
}
