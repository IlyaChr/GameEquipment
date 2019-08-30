#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>


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

    QMessageBox msgBox;
    msgBox.setText("Вы хотите быть сервером?");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int res = msgBox.exec();

    if (res == QMessageBox::Yes){
        gameField = new GameField(nullptr,true);
    }else {
        gameField = new GameField(nullptr,false);
    }

    hide();

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

    gameField->deleteLater();

    move(qApp->desktop()->availableGeometry(this).center()-rect().center());

    show();
}

