#include "mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QDateTime>
#include "field.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    resize(800, 500);
    startNew();
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    f->resize(size());
}

void MainWindow::startNew()
{
    f = new Field(30, 16, 99, this);
    f->resize(size());
    connect(f, SIGNAL(miss()), this, SLOT(lose()));
    connect(f, SIGNAL(win()), this, SLOT(win()));
    f->show();
}

void MainWindow::lose()
{
    QMessageBox msgBox;
      msgBox.setText("You Lose");
      msgBox.exec();
      f->deleteLater();
      startNew();
}

void MainWindow::win()
{
    QMessageBox msgBox;
      msgBox.setText("You win");
      msgBox.exec();
      f->deleteLater();
      startNew();
}

