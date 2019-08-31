#include "inventory.h"
#include <QHeaderView>
#include <QAbstractItemView>
#include "inventoryitem.h"
#include "db/db.h"
#include <QDebug>
#include <QMessageBox>

Inventory::Inventory(QWidget *parent):
    QTableWidget (parent)
{

   //expand cells for whole size
   horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

   setFocusPolicy(Qt::NoFocus);

}

Inventory::~Inventory()
{
    if (network){
        delete network;
    }
}

/**
 * @brief Inventory::initTable
 * @param rowSize
 * @param columnSize
 * Populate cells by InventoryItem widgets
 */
void Inventory::initTable(int rowSize, int columnSize,Network* network)
{
    setRowCount(rowSize);
    setColumnCount(columnSize);

    int slot_id = 0;

    QMap<int,int> map = Db::Instance().loadData(InventoryItem::APPLE_ID);

    int quantity = 0;

    for(int i=0 ; i<rowCount();i++){
        for (int j=0 ; j<columnCount(); j++ , slot_id++){

            quantity = map.value(slot_id);

            InventoryItem* item = new InventoryItem(this,horizontalHeader()->defaultSectionSize(),verticalHeader()->defaultSectionSize(),slot_id,quantity);

            //for db
            connect(item,&InventoryItem::saveData,this,&Inventory::saveData);

            //for network
            connect(item,&InventoryItem::dataHasChanged,network,&Network::sendMessage);
            connect(network,&Network::getMessage,item,&InventoryItem::setItem);

            setCellWidget(i,j,item);

        }
    }
}

void Inventory::saveData(int id_slot, int id_item, int quant)
{

    if (Db::Instance().saveData(id_slot,id_item,quant)){

        //qDebug()<<"Data for slot:"<<id_slot<< " saved!!!"<<endl;


    }else {

        qDebug()<<"oops data for slot:"<<id_slot<< " not saved :( "<<endl;
    }
}


