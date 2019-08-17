#include "cell.h"
#include <QPainter>
#include <QDebug>

Cell::Cell(int column, int row, QWidget *parent) :
    QWidget(parent),
    row(row),
    column(column),
    opened(false),
    marked(false),
    mined(false),
    neighbours(0)
{}

bool Cell::isMine()
{
    return mined;
}

void Cell::setMine()
{
    mined = true;
    repaint();
}

void Cell::open()
{
    qDebug() << "111" << column << row;
    if (marked) return;
    if (opened) return;
    opened = true;
    if(mined)
    {
        emit miss();
        return;
    }
    if (neighbours == 0)
        emit zeroOpened(column, row);

    repaint();
    qDebug() << "Opened cell" << column << row;
}

void Cell::incNeighbours()
{
    ++neighbours;
}

void Cell::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QPen(Qt::black, 1));
    p.setBrush(QBrush(mined ? Qt::red : Qt::gray));
    if (opened)
    {
        p.drawText(QPoint(0, 0), QString::number(neighbours));
    }
    else
    {
        p.drawRect(rect());
    }
    p.end();
}
