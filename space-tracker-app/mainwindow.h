#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QFileDialog>
#include <QDateTime>
#include <stdlib.h>
#include "viewer.h"
#include "draw.h"
#include "maincontroll.h"

#define middleTime 72
#define daysHour 24

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    public slots:
        void selectTrace(int x, int y);
    private slots:
        void on_fileSelect_clicked();
        void on_buttonRevert_clicked();
        void on_setupTime_clicked();

        void on_changeTime_sliderMoved(int position);

        void on_changeTime_sliderReleased();

        void on_informationTable_cellClicked(int row, int column);

        void on_informationTable_clicked(const QModelIndex &index);

        void on_sortButton_clicked();

        void on_drawButtonAllTrace_clicked();

        void on_loadButtonInternet_clicked();

private:
        Ui::MainWindow *ui;
        MainControll *program;
        void printTLEInfo(FormTLE newInfo);
        void refreshTime();
};

#endif // MAINWINDOW_H
