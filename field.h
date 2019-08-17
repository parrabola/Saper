#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include "cell.h"

class Field : public QWidget
{
    Q_OBJECT
public:
    Field(int w, int h, int m, QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent*);
    QPoint center();
    void placeMines(int column, int row);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void lose();
    void openNeighbours(int x, int y);
signals:
    void miss();
private:
    QVector<QVector<Cell*> > cells;
    QList<bool> m_mines;
    QList<bool> m_opened;
    int m_width;
    int m_height;
    int m_mineCount;
    bool generated;
};

#endif // FIELD_H
