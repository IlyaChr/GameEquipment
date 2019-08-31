#include "gamefield.h"
#include "ui_gamefield.h"
#include <QCloseEvent>
#include <QPixmap>


GameField::GameField(QWidget *parent,bool IsServer,Network* network) :
    QWidget(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);

    //set item image and text name
    ui->item->setPixmap(QPixmap(Item::PATH_TO_APPLE_IMG));
    ui->item->setText(Item::APPLE_NAME);

    //set inventory items widget in QTableWidget cells
    //set network
    ui->inventory->initTable(3,2,network);

    if (IsServer){
        ui->serverStatus->setText("Сервер");
        ui->serverStatus->setStyleSheet("QLabel { color : red; }");
    }else {
        ui->serverStatus->setText("Клиент");
        ui->serverStatus->setStyleSheet("QLabel { color : green ; }");
    }

}

GameField::~GameField()
{
    delete ui;
}

//for saving
void GameField::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
    emit WidgetClosed();
}

/**
 * @brief GameField::on_mainWindow_clicked
 * hide GameField widget and emit close signal for mainWindow slot
 */
void GameField::on_mainWindow_clicked()
{
    hide();
    emit WidgetClosed();
}
