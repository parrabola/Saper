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

bool Cell::open()
{
    if (marked) return false;
    if (opened) return false;
    opened = true;
    if(mined)
    {
        emit miss();
        repaint();
        return false;
    }
    if (neighbours == 0)
        emit zeroOpened(column, row);

    repaint();
    return true;
}

void Cell::incNeighbours()
{
    ++neighbours;
}

void Cell::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QPen(Qt::black, 1));
    p.setBrush(QBrush(marked ? Qt::red : Qt::gray));
    if (opened)
    {
        QMap<int, QColor> colors;
        colors.insert(0, Qt::transparent);
        colors.insert(1, Qt::blue);
        colors.insert(2, Qt::red);
        colors.insert(3, Qt::green);
        colors.insert(4, Qt::yellow);
        colors.insert(5, Qt::darkMagenta);
        colors.insert(6, Qt::lightGray);
        colors.insert(7, Qt::magenta);
        colors.insert(8, Qt::darkCyan);
        p.setPen(QPen(colors[neighbours], 2));
        p.setFont(QFont("Tahoma", width() * 0.7, QFont::Bold));
        p.drawText(rect(), Qt::AlignCenter, mined ? "X" : QString::number(neighbours));
    }
    else
    {
        p.drawRect(rect());
    }
    p.end();
}

void Cell::mark()
{
    marked = !marked;
    repaint();
}
