#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include "network/network.h"

namespace Ui {
class GameField;
}

class GameField : public QWidget
{
    Q_OBJECT

public:
    explicit GameField(QWidget *parent = nullptr,bool server = true,Network* network = nullptr);
    ~GameField() override;

protected:

    void closeEvent (QCloseEvent *event) override;


private slots:

    void on_mainWindow_clicked();

private:
    Ui::GameField *ui;


signals:
    void WidgetClosed();
};

#endif // GAMEFIELD_H
