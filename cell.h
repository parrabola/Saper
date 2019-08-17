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
    void open();
    void incNeighbours();
    void paintEvent(QPaintEvent*);
signals:
    void miss();
    void zeroOpened(int x, int y);

public slots:
private:
    int row;
    int column;
    bool marked;
    bool opened;
    bool mined;
    int neighbours;
};

#endif // CELL_H
