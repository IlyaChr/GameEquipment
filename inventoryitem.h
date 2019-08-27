#ifndef INVENTORYSUBJECT_H
#define INVENTORYSUBJECT_H

#include "item.h"

class InventoryItem : public Item
{
    Q_OBJECT
public:
    explicit InventoryItem( QWidget* parent = nullptr, int width = 1,int hight = 1,int slot_id = 0,int quantityItems = 0);
    ~InventoryItem() override;


    const static QString DELIMITER;
    const static QString APPLE_SOUND_PATH;

protected:
    void dragEnterEvent( QDragEnterEvent* event) override;
    void dropEvent( QDropEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int quantityItems = 0;
    int slot_id = 0;

signals:
    void saveData(int id_slot,int id_item,int quant);

};

#endif // INVENTORYSUBJECT_H
