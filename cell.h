#ifndef CELL_H
#define CELL_H

#include <QWidget>

class Cell : public QWidget
{
    Q_OBJECT
public:
    explicit Cell(int column, int row, QWidget *parent = nullptr);
    bool isMine();
    void setMine();
    bool open();
    bool opened();
    bool marked();
    void incNeighbours();
    void paintEvent(QPaintEvent*);
    void mark();
    int neighbours();
signals:
    void miss();
    void zeroOpened(int x, int y);

public slots:
private:
    int row;
    int column;
    bool m_marked;
    bool m_opened;
    bool mined;
    int m_neighbours;
};

#endif // CELL_H
