#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "field.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT // НЁХ

public:
    explicit MainWindow(QWidget *parent = 0); // почитать в гугле про эксплисит
    ~MainWindow();
    void resizeEvent(QResizeEvent *);

private:
    Field *f;
    void startNew();

private slots:
    void lose();
    void win();
};

#endif // MAINWINDOW_H
