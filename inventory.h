#ifndef INVENTORY_H
#define INVENTORY_H

#include <QTableWidget>

class Inventory : public QTableWidget
{
    Q_OBJECT

public:
    explicit Inventory(QWidget *parent = nullptr);

    void initTable(int rowSize, int columnSize);

private:
};

#endif // INVENTORY_H
