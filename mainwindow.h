#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamefield.h"
#include "gamefield.h"
#include "network/servergame.h"
#include "network/clientgame.h"


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

    bool initNetwork(bool isServer);

private:
    Ui::MainWindow *ui;

    GameField* gameField = nullptr;

    Network* network = nullptr;

};

#endif // MAINWINDOW_H
