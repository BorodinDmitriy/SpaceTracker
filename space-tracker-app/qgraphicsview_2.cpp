#include "qgraphicsview_2.h"

MyGraphicsView::MyGraphicsView(QWidget *&a): QGraphicsView(a)
{
	setInteractive(true);   
	setMouseTracking(true);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *pt)
{  
    moved(pt->x(), pt->y());
    return;
}

void MyGraphicsView::mousePressEvent(QMouseEvent * pt)
{
    clicked(pt->x(), pt->y());
    return;
}
