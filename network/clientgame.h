#ifndef CLIENTGAME_H
#define CLIENTGAME_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

class ClientGame : public QObject
{
    Q_OBJECT
public:
    explicit ClientGame();
    ~ClientGame();

private:
    QTcpSocket* socket = nullptr;
    QByteArray data;

    QJsonDocument doc;
    QJsonParseError parseError;

private slots:
    void sockReady();
    void sockDisk();

public slots:
    bool connectToServer();
    void sendMessage(int id_slot,int id_item,int quant);

signals:
    void getMessage(int id_slot,int id_item,int quant);
};

#endif // CLIENTGAME_H
