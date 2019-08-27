#include "gamefield.h"
#include "ui_gamefield.h"
#include <QCloseEvent>
#include <QPixmap>

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);

    //set item image and text name
    ui->item->setPixmap(QPixmap(Item::PATH_TO_APPLE_IMG));
    ui->item->setText(Item::APPLE_NAME);

    //set inventory items widget in QTableWidget cells
    ui->inventory->initTable(3,2);
}

GameField::~GameField()
{
    delete ui;
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
