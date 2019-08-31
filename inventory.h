#ifndef INVENTORY_H
#define INVENTORY_H

#include <QTableWidget>
#include "network/network.h"

class Inventory : public QTableWidget
{
    Q_OBJECT

public:
    explicit Inventory(QWidget *parent = nullptr);
    ~Inventory() override;

    void initTable(int rowSize, int columnSize,Network* network = nullptr);

private:
    bool server = true;

    Network* network = nullptr;

private slots:
    void saveData(int id_slot,int id_item,int quant);

signals:
    void error();
};

#endif // INVENTORY_H
