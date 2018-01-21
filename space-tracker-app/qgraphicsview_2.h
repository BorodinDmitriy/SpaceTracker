#ifndef QGRAPHICSVIEW_2_H

#define QGRAPHICSVIEW_2_H

#include <QMouseEvent>
#include <QGraphicsView>
#include <QObject>
#include <QTimer>

class MyGraphicsView : public QGraphicsView

{
    Q_OBJECT
	signals:
        void moved(int,int);
        void clicked(int,int);
    protected:
        virtual void mouseMoveEvent(QMouseEvent *);
        virtual void mousePressEvent(QMouseEvent *);
	public:
        MyGraphicsView(QWidget *&);
};

#endif
