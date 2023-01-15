#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecounter.hh"
#include <string>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxN->setRange(0,760);
    ui->spinBoxG->setRange(0,120);
    ui->spinBoxP->setRange(0,250);
    ui->spinBoxE->setRange(0,5);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countPushButton_clicked()
{
    unsigned int n = ui->spinBoxN->value();
    unsigned int g = ui->spinBoxG->value();
    unsigned int p = ui->spinBoxP->value();
    unsigned int e = ui->spinBoxE->value();

    int final_grade = count_final_grade(n,g,p,e);
    QString final_text = "Total grade: ";
    final_text.push_back(QString::number(final_grade));
    ui->textBrowser->setText(final_text);
}

