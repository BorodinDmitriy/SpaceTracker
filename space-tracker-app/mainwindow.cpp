#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(0));
    QObject::connect(ui->fieldDraw, SIGNAL(clicked(int,int)), this, SLOT(selectTrace(int,int)));
    program = new MainControll(ui->fieldDraw, ui->informationTable);
    refreshTime();
    return;
}

void MainWindow::selectTrace(int x, int y)
{
    program->selectObjectOnTable(x, y);
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileSelect_clicked()
{
    QString file = QFileDialog::getOpenFileName(0, "Выберите файл загрузки", " ", tr(".*"));
    program->loadTLEforDB(file.toStdString());
    return;
}

void MainWindow::on_buttonRevert_clicked()
{
    program->revertMap();
    return;
}

void MainWindow::printTLEInfo(FormTLE newInfo)
{
    ui->valueAltitude->setText(QString("%1").arg(newInfo.lastHeight));
    ui->valueLatitude->setText(QString("%1").arg(newInfo.lastLatitude));
    ui->valueLongitude->setText(QString("%1").arg(newInfo.lastLongitude));
    ui->valueVelocity->setText(QString("%1").arg(newInfo.lastSpeed));
    return;
}

void MainWindow::on_setupTime_clicked()
{
    QDateTime dateTime;
    QTime time;
    QDate date;
    int hour = ui->boxHour->value();
    int minute = ui->boxMinute->value();
    time.setHMS(hour,minute,0,0);
    int day = ui->boxDay->value();
    int month = ui->boxMonth->value();
    int year = ui->boxYear->value();
    date.setDate(year,month,day);
    dateTime.setDate(date);
    dateTime.setTime(time);
    program->setupDate(dateTime);
    refreshTime();
    return;
}

void MainWindow::refreshTime()
{
    QDateTime currentDateTime = program->getDate();
    int day = currentDateTime.date().day();
    int month = currentDateTime.date().month();
    int year = currentDateTime.date().year();
    int hour = currentDateTime.time().hour();
    int minute = currentDateTime.time().minute();
    QString newText = QString("%1%2%3%4%5").arg(day, 2).arg(month, 2).arg(year, 4).arg(hour, 2).arg(minute, 2);
    ui->dateTime->setText(newText);
    return;
}

void MainWindow::on_changeTime_sliderMoved(int position)
{
    ui->currentValue->setText(QString("%1").arg(position - middleTime));
    return;
}

void MainWindow::on_changeTime_sliderReleased()
{
    int value = ui->changeTime->value();
    if (value == 0 || value == 144)
    {
        ui->changeTime->setValue(72);
        ui->currentValue->setText("0");
    }
    QDateTime newDateTime = program->getDate();
    int hour = (value - middleTime) % daysHour;
    int day = (value - middleTime) / daysHour;
    int days = newDateTime.date().day() + day;
    newDateTime.setDate( QDate(newDateTime.date().year(), newDateTime.date().month(), days));
    int hours = newDateTime.time().hour() + hour;
    newDateTime.setTime( QTime(hours, newDateTime.time().minute(), newDateTime.time().second()));
    program->setupDate(newDateTime);
    refreshTime();
    return;
}

void MainWindow::on_informationTable_cellClicked(int row, int column)
{
    FormTLE *infoOfTLE;
    program->clearMap();
    infoOfTLE = program->selectObjectOnMap(row);
    if (infoOfTLE != NULL)
        printTLEInfo(*infoOfTLE);
    return;
}

void MainWindow::on_informationTable_clicked(const QModelIndex &index)
{
}

void MainWindow::on_sortButton_clicked()
{
    int indexRow = ui->orderBox->currentIndex();
    Qt::SortOrder order;
    if (ui->orderBoxType->isChecked() == true)
        order = Qt::DescendingOrder;
    else
        order = Qt::AscendingOrder;
    program->sort(indexRow, order);
    return;
}

void MainWindow::on_drawButtonAllTrace_clicked()
{
    program->drawAllTrace();
    return;
}

void MainWindow::on_loadButtonInternet_clicked()
{
    program->loadTLEforDBInter();
    return;
}
