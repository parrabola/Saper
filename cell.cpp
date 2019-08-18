#include "cell.h"
#include <QPainter>
#include <QDebug>

Cell::Cell(int column, int row, QWidget *parent) :
    QWidget(parent),
    row(row),
    column(column),
    m_opened(false),
    m_marked(false),
    mined(false),
    m_neighbours(0)
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
    if (m_marked) return false;
    if (m_opened) return false;
    m_opened = true;
    if(mined)
    {
        emit miss();
        repaint();
        return false;
    }
    if (m_neighbours == 0)
        emit zeroOpened(column, row);

    repaint();
    return true;
}

bool Cell::opened()
{
    return m_opened;
}

bool Cell::marked()
{
    return m_marked;
}

void Cell::incNeighbours()
{
    ++m_neighbours;
}

void Cell::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(QPen(Qt::black, 1));
    p.setBrush(QBrush(m_marked ? Qt::red : Qt::gray));
    if (m_opened)
    {
        QMap<int, QColor> colors;
        colors.insert(0, Qt::transparent);
        colors.insert(1, Qt::blue);
        colors.insert(2, Qt::red);
        colors.insert(3, Qt::green);
        colors.insert(4, Qt::darkRed);
        colors.insert(5, Qt::darkMagenta);
        colors.insert(6, Qt::lightGray);
        colors.insert(7, Qt::magenta);
        colors.insert(8, Qt::darkCyan);
        p.setPen(QPen(colors[m_neighbours], 2));
        p.setFont(QFont("Tahoma", width() * 0.7, QFont::Bold));
        p.drawText(rect(), Qt::AlignCenter, mined ? "X" : QString::number(m_neighbours));
    }
    else
    {
        p.drawRect(rect());
    }
    p.end();
}

void Cell::mark()
{
   if (opened())
       return;
    m_marked = !m_marked;
    repaint();
}

int Cell::neighbours()
{
    return m_neighbours;
}
