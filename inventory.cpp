#include "inventory.h"
#include <QHeaderView>
#include <QAbstractItemView>
#include "inventoryitem.h"

Inventory::Inventory(QWidget *parent):
    QTableWidget (parent)
{

   //expand cells for whole size
   horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

/**
 * @brief Inventory::initTable
 * @param rowSize
 * @param columnSize
 * Populate cells by InventoryItem widgets
 */
void Inventory::initTable(int rowSize, int columnSize)
{
    setRowCount(rowSize);
    setColumnCount(columnSize);

    for(int i=0 ; i<rowCount();i++){
        for (int j=0 ; j<columnCount(); j++){

            InventoryItem* subject = new InventoryItem(this,horizontalHeader()->defaultSectionSize(),verticalHeader()->defaultSectionSize());

            setCellWidget(i,j,subject);
        }
    }
}


