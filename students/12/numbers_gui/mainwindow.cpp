/* 2048
 *
 * Desc:
 * This Class implements a grafical interface to an existing progmam
 * that handels the game mechanics for the gamme 2048.
 * see instructions.txt folder for game instructions and notes
 *
 * Program author:
 * Name: Ilari Hietala
 * Student number: H291752
 * UserID: hgilhi
 * E-Mail: ilari.hietala@tuni.fi
 *
 * Notes about the program and it's implementation:
 *  see instructions.txt folder
 * */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "numbertile.hh"
#include "gameboard.hh"
#include <QDebug>
#include <cmath>
#include <memory>


#include <iostream>

const Coords UP = {0, -1};
const Coords LEFT = {-1, 0};
const Coords DOWN = {0, 1};
const Coords RIGHT = {1, 0};

const int OFFSET = 65;

std::vector<QString> COLORS = {"crimson", "sienna", "darkorange", "aqua", "lime", "gold",
                                        "grey", "yellow", "salmon", "blue", "pink"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setup for the spinboxes and reset button
    spin_box_goal = new QSpinBox(this);
    spin_box_goal->setGeometry(QRect(QPoint(670, 50), QSize(50, 20)));
    spin_box_goal->setRange(0,20);
    spin_box_goal->setValue(11);

    spin_box_seed = new QSpinBox(this);
    spin_box_seed->setGeometry(QRect(QPoint(670, 75), QSize(50, 20)));
    spin_box_seed->setValue(1);

    push_button_reset = new QPushButton("Reset", this);
    push_button_reset->setGeometry(QRect(QPoint(670, 100), QSize(50, 20)));
    connect(push_button_reset, &QPushButton::pressed, this, &MainWindow::on_push_button_reset_clicked);

    ui->info_screen->setText("Have fun");

    tile_labels_ = {};
    board_ = {};

    init_empty();


}

MainWindow::~MainWindow()
{


    for (int y=0; y < SIZE; ++y) {
        for (int x=0; x < SIZE; ++x) {
            delete tile_labels_.at(y).at(x);
            tile_labels_.at(y).at(x) = nullptr;
        }
    }



    delete spin_box_goal;
    delete spin_box_seed;
    delete push_button_reset;

    delete ui;
}

void MainWindow::init_empty()
{

    board_.init_empty();

    board_.fill(spin_box_seed->value());

    std::vector<QLabel*> row;
    for( int i = 0; i < SIZE; ++i)
    {
        row.push_back(nullptr);
    }
    for( int i = 0; i < SIZE; ++i)
    {
        tile_labels_.push_back(row);
    }
    // creates a label for every square of the board
    for (int y=0; y < SIZE; ++y) {
        for (int x=0; x < SIZE; ++x) {

            int current_value = board_.get_item({x,y})->get_value();
            if (current_value == 0) {
                tile_labels_.at(y).at(x) = new QLabel("", this);
            } else {
                tile_labels_.at(y).at(x) = new QLabel(QString::number(current_value), this);

            }

            tile_labels_.at(y).at(x)->setAlignment(Qt::AlignCenter);
            tile_labels_.at(y).at(x)->setFixedHeight(60);
            tile_labels_.at(y).at(x)->setFixedWidth(60);

            tile_labels_.at(y).at(x)->move(100 + OFFSET*x,100 + OFFSET*y);
        }
    }

    update_ui();
}

void MainWindow::update_ui()
{
    for (int y=0; y < SIZE; ++y) {
        for (int x=0; x < SIZE; ++x) {
            int current_value = board_.get_item({x,y})->get_value();
            if (current_value != 0) {
                tile_labels_.at(y).at(x)->setText(QString::number(current_value));
                tile_labels_.at(y).at(x)->move(OFFSET + OFFSET*x,OFFSET + OFFSET*y);
                QString background_color = "background-color:";
                background_color.append(COLORS.at(log(current_value)/log(2)-1));
                tile_labels_.at(y).at(x)->setStyleSheet(background_color);
            } else {
                tile_labels_.at(y).at(x)->setText("");
                tile_labels_.at(y).at(x)->move(OFFSET + OFFSET*x,OFFSET + OFFSET*y);
                tile_labels_.at(y).at(x)->setStyleSheet("background-color:");
            }
        }
    }
}
// the button_cliced methods all check for win/lost senario,
// create a new value to the board and uptade the ui
void MainWindow::on_pushButtonLeft_clicked()
{
    if (board_.move(LEFT, pow(2,spin_box_goal->value())))  {
        ui->info_screen->setText("You Won");
        disable_move_buttons(true);
    } else if (board_.is_full()) {
        ui->info_screen->setText("You Lost");
        disable_move_buttons(true);
    } else {
        board_.new_value();
        update_ui();
    }
}

void MainWindow::on_pushButtonUp_clicked()
{
    if (board_.move(UP, pow(2,spin_box_goal->value())))  {
        ui->info_screen->setText("You Won");
        disable_move_buttons(true);
    } else if (board_.is_full()) {
        ui->info_screen->setText("You Lost");
        disable_move_buttons(true);
    } else {
        board_.new_value();
        update_ui();
    }
}

void MainWindow::on_pushButtonDown_clicked()
{
    if (board_.move(DOWN, pow(2,spin_box_goal->value())))  {
        ui->info_screen->setText("You Won");
        disable_move_buttons(true);
    } else if (board_.is_full()) {
        ui->info_screen->setText("You Lost");
        disable_move_buttons(true);
    } else {
        board_.new_value();
        update_ui();
    }
}

void MainWindow::on_pushButtonRight_clicked()
{
    if (board_.move(RIGHT, pow(2,spin_box_goal->value())))  {
        ui->info_screen->setText("You Won");
        disable_move_buttons(true);
    } else if (board_.is_full()) {
        ui->info_screen->setText("You Lost");
        disable_move_buttons(true);
    } else {
        board_.new_value();
        update_ui();
    }
}

void MainWindow::on_push_button_reset_clicked()
{
    board_.whipe_board();
    board_.init_empty();
    board_.fill(spin_box_seed->value());
    ui->info_screen->setText("Good luck");
    update_ui();
    disable_move_buttons(false);
}

void MainWindow::disable_move_buttons(bool enabler)
{
    ui->pushButtonDown->setDisabled(enabler);
    ui->pushButtonLeft->setDisabled(enabler);
    ui->pushButtonRight->setDisabled(enabler);
    ui->pushButtonUp->setDisabled(enabler);

}



