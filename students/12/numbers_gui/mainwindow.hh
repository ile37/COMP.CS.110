#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QTextBrowser>
#include "gameboard.hh"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init_empty();

    void update_ui();

    void on_push_button_reset_clicked();

private slots:

    void on_pushButtonLeft_clicked();

    void on_pushButtonUp_clicked();

    void on_pushButtonDown_clicked();

    void on_pushButtonRight_clicked();



    // if enabler true all move buttons are diseabled
    void disable_move_buttons(bool enabler);


private:
    Ui::MainWindow *ui;

    std::vector<std::vector<QLabel*>> tile_labels_;

    GameBoard board_;

    QSpinBox *spin_box_goal;
    QSpinBox *spin_box_seed;

    QPushButton *push_button_reset;


};
#endif // MAINWINDOW_HH
