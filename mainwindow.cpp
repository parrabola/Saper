#include "mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QDateTime>
#include "field.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    resize(800, 500);
//   show();
//    myRect* a = new myRect(this);
//    a->resize(size());
//    a->show();
//    myRect* a2 = new myRect(a);
//    a2->show();
//    myRect* a3 = new myRect(a2);
//    a3->show();
    f = new Field(40, 25, 99, this);
    f->resize(size());
    connect(f, SIGNAL(miss()), this, SLOT(lose()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    f->resize(size());
}

void MainWindow::lose()
{
    qDebug() << "You lose";
}

