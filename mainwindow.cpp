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
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("Вы хотите быть сервером или клиентом?");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setButtonText(QMessageBox::Yes,"Сервер");
    msgBox.setButtonText(QMessageBox::No,"Клиент");
    int res = msgBox.exec();

    if (res == QMessageBox::Yes){
        //attempt start server
        if(!initNetwork(true) || !network){
            return;
        }
        gameField = new GameField(nullptr,true,network);
    }else {
        //attempt start client
        if(!initNetwork(false) || !network){
            return;
        }
        gameField = new GameField(nullptr,false,network);
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


bool MainWindow::initNetwork(bool isServer)
{
    QString errorMes;

    if (isServer){
        network = new ServerGame();
        errorMes = "Ошибка создания сервера!";
    }else {
        network = new ClientGame();
        errorMes = "Ошибка подключения к серверу!";
    }

    if (!network->start()){
        QMessageBox::critical(this, "Внимание",errorMes);
        return false;

    }
    return true;
}



