#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_newGame_clicked
 * launch new game
 */
void MainWindow::on_newGame_clicked()
{
    hide();

    gameField = new GameField();

    connect( gameField, SIGNAL(WidgetClosed()), this, SLOT(backToMainWindow()));

    gameField->show();

}

/**
 * @brief MainWindow::on_exitGame_clicked
 * end of the game
 */
void MainWindow::on_exitGame_clicked()
{

    QApplication::quit();
}

/**
 * @brief MainWindow::backToMainWindow
 * slot for return to mainWindow
 */
void MainWindow::backToMainWindow()
{
    if (gameField){
        disconnect( gameField, SIGNAL(WidgetClosed()), this, SLOT(backToMainWindow()));
    }

    delete gameField;

    move(qApp->desktop()->availableGeometry(this).center()-rect().center());

    show();
}

