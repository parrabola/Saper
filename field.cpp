#include "field.h"
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

Field::Field(int w, int h, int m, QWidget *parent) :
    QWidget(parent),
    m_width(w),
    m_height(h),
    m_mineCount(m),
    generated(false),
    opened(0)
{
    for (int x = 0; x < w; ++x)
    {
        QVector<Cell*> column;
        for (int y = 0; y < h; ++y)
        {
            Cell* cell = new Cell(x, y, this);
            connect(cell, SIGNAL(miss()), this, SLOT(lose()));
            connect(cell, SIGNAL(zeroOpened(int,int)), this, SLOT(openNeighbours(int,int)));
            column.append(cell);
        }
        cells.append(column);
    }
}

void Field::resizeEvent(QResizeEvent *)
{
    int cS = qMin(width()/m_width, height()/m_height);
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            Cell* c = cells[x][y];
            c->resize(cS, cS);
            c->move(x * cS, y * cS);
        }
    }
}

QPoint Field::center()
{
    return QPoint(width() / 2, height() / 2);
}

void Field::placeMines(int column, int row)
{
    int placed = 0;
    while(placed < m_mineCount)
    {
        int r = qrand() % m_height;
        int c = qrand() % m_width;
        if (qMax(qAbs(column - c), qAbs(row - r)) < 2)
        {
            continue;
        }
        Cell* cell = cells[c][r];
        if (cell->isMine()) continue;
        cell->setMine();
        ++placed;
        for (int col = qMax(c-1, 0); col <= qMin(c+1, m_width -1); ++col)
        {
            for (int rw = qMax(r-1, 0); rw <= qMin(r+1, m_height -1); ++rw)
            {
                cells[col][rw]->incNeighbours();
            }
        }
    }
    generated = true;
}

void Field::mouseReleaseEvent(QMouseEvent *event)
{
    int cS = qMin(width()/m_width, height()/m_height);
    int column = event->x()/cS;
    int row = event->y()/cS;
    if (row >= m_height || column >= m_width) return;
    switch (event->button()) {
    case Qt::LeftButton:
        if (!generated)
        {
            placeMines(column, row);
            cells[column][row]->open();
            ++opened;
            checkWin();
            return;
        }
        if (cells[column][row]->open())
        {
            ++opened;
            checkWin();
        }
        break;
    case Qt::RightButton:
        cells[column][row]->mark();
        break;
    case Qt::MiddleButton:
        break;
    default:
        break;
    }
}

void Field::lose()
{
    emit miss();
}

void Field::openNeighbours(int x, int y)
{
    for (int column = qMax(x-1, 0); column <= qMin(x+1, m_width -1); ++column)
    {
        for (int row = qMax(y-1, 0); row <= qMin(y+1, m_height -1); ++row)
        {
            if (cells[column][row]->open()) ++opened;
            checkWin();
        }
    }
}

void Field::checkWin()
{
    if (opened == m_width*m_height - m_mineCount)
    {
        emit win();
    }
}
