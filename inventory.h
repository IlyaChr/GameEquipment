#ifndef INVENTORY_H
#define INVENTORY_H

#include <QTableWidget>
#include "network/servergame.h"
#include "network/clientgame.h"

class Inventory : public QTableWidget
{
    Q_OBJECT

public:
    explicit Inventory(QWidget *parent = nullptr);
    ~Inventory() override;

    void initTable(int rowSize, int columnSize,bool server = true);

private:
    bool server = true;

    ServerGame* myServer = nullptr;
    ClientGame* myClient = nullptr;

private slots:
    void saveData(int id_slot,int id_item,int quant);
    void initNetwork(bool server = true);

signals:
    void error();
};

#endif // INVENTORY_H
