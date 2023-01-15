#include "mainwindow.hh"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countButton_clicked()
{
    float weight = ui->weightLineEdit->displayText().toFloat();
    float height = ui->heightLineEdit->displayText().toFloat()/100;

    if (weight == 0 or height == 0) {
        ui->resultLabel->setText("Cannot count");
    } else {
        float bmi = weight/(height*height);

        ui->resultLabel->setText(QString::number(bmi));

        if (bmi > 25) {
            ui->infoTextBrowser->setText("You are overweight.");
        } else if (bmi < 18.5) {
            ui->infoTextBrowser->setText("You are underweight.");
        } else {
            ui->infoTextBrowser->setText("Your weight is normal.");
        }
    }


}

