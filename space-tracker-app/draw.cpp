#include "draw.h"

Draw::Draw(void *newGraphicsView, void *tableWidget)
{
    graphicsView = (QGraphicsView *)newGraphicsView;
    tblWidget = (QTableWidget *)tableWidget;
    scene = new QGraphicsScene(graphicsView);
    if (scene == NULL)
        throw MemoryAllocationError();
    int width = graphicsView->width();
    int height = graphicsView->height();
    image = QImage(width ,height, QImage::Format_RGB888);
    pen.setColor(QColor(255, 0, 0, 255));
    pen.setWidth(3);
    pixmap.load("./map.png");
    rateX = pixmap.width() / 360.0;
    rateY = pixmap.height() / 180.0;
    scene->addPixmap(pixmap);
    graphicsView->setGeometry(40, 30, pixmap.width() + 2, pixmap.height() + 2);
    drawMap();
    return;
}

Draw::~Draw()
{
    delete scene;
}

void Draw::sortTableInfrormation(const int column, const Qt::SortOrder order)
{
    if(column < 0 || column > tblWidget->columnCount())
        return;
    tblWidget->sortItems(column, order);
    tblWidget->show();
    return;
}

void Draw::drawMap()
{
    if (scene == NULL)
        throw NullPointer();
    graphicsView->setScene(scene);
    return;
}

void Draw::selectObjectOnTable(const int noradID)
{
    int m = tblWidget->rowCount();
    int n = tblWidget->columnCount();
    int indexRow = -1;
    for (int i = 0; i < m - 1; i++)
    {
        if(tblWidget->item(i, 0)->text() == QString::number(noradID))
            indexRow = i;
        for (int j = 0; j < n; j++)
        {
            tblWidget->item(i, j)->setSelected(false);
        }
    }
    if (indexRow != -1)
    {
        for (int j = 0; j < n; j++)
        {
            tblWidget->item(indexRow, j)->setSelected(true);
        }
    }
    return;
}

int Draw::getNoradID(const int row)
{
    int m = tblWidget->rowCount();
    if (row < 0 || row > m)
        return -1;
    return tblWidget->item(row, 0)->text().toInt();
}


void Draw::drawTrace(QList<QPoint> trackPoint, QColor color)
{
    image = pixmap.toImage();
    stackImage.push(image);
    int n = trackPoint.count();
    QPoint *pointOnMap = new QPoint[n];
    QPainter painter(&image);
    pen.setColor(color);
    pen.setBrush(QBrush(color));
    painter.setPen(pen);
    QPoint transformPoint;
    for (int i = 0; i < n; i++)
    {
        transformPoint = QPoint(getInitX(trackPoint[i].x()), getInitY(trackPoint[i].y()));
        pointOnMap[i] = transformPoint;
    }
    painter.drawPolyline(pointOnMap, n);
    for (int i = 0; i < n; i++)
    {
        painter.drawEllipse(pointOnMap[i].x(), pointOnMap[i].y(), radiusOfPoint, radiusOfPoint);
    }
    pixmap.convertFromImage(image);
    scene->addPixmap(pixmap);
    delete pointOnMap;
    return;
}

void Draw::revert()
{
    if (stackImage.size() >= 1)
    {
        image = stackImage.top();
        stackImage.pop();
        pixmap = QPixmap::fromImage(image);
        scene->addPixmap(pixmap);
    }
    drawMap();
    return;
}
void Draw::clear()
{
    if (stackImage.size() >= 1)
    {
        while (stackImage.size() != 1)
        {
            stackImage.pop();
        }
        revert();
    }
    return;
}

int Draw::getX(int x)
{
    return x * rateX - longitude;
}

int Draw::getY(int y)
{
    return y * rateY - latitude;
}

int Draw::getInitX(int x)
{
    if ( x > longitude)
        return (x - longitude) * rateX;
    else
        return (x + longitude) * rateX;
}
int Draw::getInitY(int y)
{
    return (- y + latitude) * rateY;
}

void Draw::addToTable(int number, char *name, char typeObject, char *typeOrbit, char *OGP)
{
    int rows = tblWidget->rowCount();
    tblWidget->setRowCount(rows+1);
    tblWidget->setColumnCount(5);
    QTableWidgetItem *tableItem = NULL;
    tableItem = new QTableWidgetItem(QString("%1").arg(number));
    if (tableItem == NULL)
        throw MemoryAllocationError();
    tblWidget->setItem(rows, 0, tableItem);

    tableItem = NULL;
    tableItem = new QTableWidgetItem(QString("%1").arg(name));
    if (tableItem == NULL)
        throw MemoryAllocationError();
    tblWidget->setItem(rows, 1, tableItem);

    tableItem = NULL;
    tableItem = new QTableWidgetItem(QString("%1").arg(typeObject));
    if (tableItem == NULL)
        throw MemoryAllocationError();
    tblWidget->setItem(rows, 2, tableItem);

    tableItem = NULL;
    tableItem = new QTableWidgetItem(QString("%1").arg(typeOrbit));
    if (tableItem == NULL)
        throw MemoryAllocationError();
    tblWidget->setItem(rows, 3, tableItem);

    tableItem = NULL;
    tableItem = new QTableWidgetItem(QString("%1").arg(OGP));
    if (tableItem == NULL)
        throw MemoryAllocationError();
    tblWidget->setItem(rows, 4, tableItem);

    tblWidget->show();
    return ;
}

void Draw::deleteFromTable(const int row)
{
    int rows = tblWidget->rowCount();
    QTableWidgetItem *tableItem = NULL;
    if (row - 1 <= rows - 1)
    {
        for (int i = row; i <= rows - 1; i++)
        {
            for (int j = 0; j < 5; j++)
            {

                tableItem = new QTableWidgetItem(tblWidget->item(i, j)->text());
                if (tableItem == NULL)
                    throw MemoryAllocationError();
                tblWidget->setItem(i - 1, j, tableItem);
            }
        }
        tblWidget->setRowCount(rows - 1);
        tblWidget->show();
    }
    return;
}

void Draw::clearMap()
{
    pixmap.load("./map.png");
    scene->addPixmap(pixmap);
    drawMap();
    return;
}

void Draw::getScale(double *width, double *height)
{
    (*width) = rateX;
    (*height) = rateY;
    return;
}
