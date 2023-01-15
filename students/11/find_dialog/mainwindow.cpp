#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <fstream>
#include <string>
#include <iostream>



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

void MainWindow::on_fileLineEdit_editingFinished()
{
    ui->textBrowser->toPlainText() = QString("dfdsa");
    QString file_name = ui->fileLineEdit->displayText();

    std::ifstream input(file_name.toStdString());

    if (not input){

        ui->textBrowser->setText("File not found");
    } else {
        if (ui->keyLineEdit->displayText().length() == 0) {
            ui->textBrowser->setText("File found");
        } else {
            std::string line;
            std::string word = ui->keyLineEdit->displayText().toStdString();
            if (not ui->matchCheckBox->isChecked()) {

                while( getline( input, line) ) {
                    for (unsigned long i = 0; i < line.length(); ++i) {
                        line.at(i) = toupper(line.at(i));
                        if (i < word.length()) {
                            word.at(i) = toupper(word.at(i));
                        }
                    }
                    if(line.find(word) != std::string::npos) {
                        ui->textBrowser->setText("Word found");
                        return;
                    }
                }
                ui->textBrowser->setText("Word not found");
            } else {
                while( getline( input, line) ) {
                    if(line.find(ui->keyLineEdit->displayText().toStdString()) != std::string::npos) {
                        ui->textBrowser->setText("Word found");
                        return;
                    }

                }
                ui->textBrowser->setText("Word not found");
            }

        }
    }
}

void MainWindow::on_findPushButton_clicked()
{
    on_fileLineEdit_editingFinished();
}


void MainWindow::on_matchCheckBox_clicked()
{
    on_fileLineEdit_editingFinished();
    ui->textBrowser->toPlainText();
}

