#ifndef DRAW_H
#define DRAW_H

using namespace std;
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTableWidget>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <stack>
#include <string>
#include "exceptions.h"

#define radiusOfPoint 4
#define longitude 180
#define latitude 90

class Draw
{
    public:
        Draw(void *newGraphicsView, void *tableWidget);
        ~Draw();
        void sortTableInfrormation(const int column, const Qt::SortOrder order);
        void selectObjectOnTable(const int noradID);
        void selectObjectOnMap(const int indexRow);
        int getNoradID(const int row);
        void drawMap();
        void drawTrace(QList<QPoint> trackPoint, QColor color);
        void revert();
        void clear();
        int getInitX(int x);
        int getInitY(int y);
        int getX(int x);
        int getY(int y);
        void addToTable(int number,char *name,char typeObject,char *typeOrbit,char *OGP);
        void deleteFromTable(const int row);
        void clearMap();
        void getScale(double *width, double *height);
    private:
        QTableWidget *tblWidget;
        QGraphicsView *graphicsView;
        QGraphicsScene *scene;
        stack<QImage> stackImage;
        QImage image;
        QPixmap pixmap;
        QPen pen;
        double rateX; // масштаб отображения по х
        double rateY; // масштаб отображения по у
};

#endif // DRAW_H
