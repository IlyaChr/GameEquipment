#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>

namespace Ui {
class GameField;
}

class GameField : public QWidget
{
    Q_OBJECT

public:
    explicit GameField(QWidget *parent = nullptr);
    ~GameField() override;

private slots:

    void on_mainWindow_clicked();

private:
    Ui::GameField *ui;


signals:
    void WidgetClosed();
};

#endif // GAMEFIELD_H
