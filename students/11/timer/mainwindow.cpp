#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_function()));
    timer->start(1000);
    timer->stop();

    ui->lcdNumberMin->setAutoFillBackground(true);
    ui->lcdNumberSec->setAutoFillBackground(true);

    QPalette Pal = ui->lcdNumberMin->palette();
    Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::green);
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::blue);
    ui->lcdNumberMin->setPalette(Pal);

    QPalette Pal2 = ui->lcdNumberSec->palette();
    Pal2.setColor(QPalette::Normal, QPalette::WindowText, Qt::red);
    Pal2.setColor(QPalette::Normal, QPalette::Window, Qt::black);
    ui->lcdNumberSec->setPalette(Pal2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timer_function()
{
    sec = sec + 1;
    if (sec == 60) {
        min = min +1;
        sec = 0;
        ui->lcdNumberMin->display(min);
    }
    ui->lcdNumberSec->display(sec);
}

void MainWindow::on_startButton_clicked()
{
    if (not timer->isActive()) {
        timer->start();
    }

}

void MainWindow::on_stopButton_clicked()
{
    if (timer->isActive()) {
        timer->stop();
    }
}


void MainWindow::on_resetButton_clicked()
{
    timer->stop();
    sec = 0;
    min = 0;
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);

}

