#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamefield.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_newGame_clicked();

    void on_exitGame_clicked();

    void backToMainWindow();

private:
    Ui::MainWindow *ui;

    GameField* gameField = nullptr;

};

#endif // MAINWINDOW_H
