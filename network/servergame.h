#ifndef SERVERGAME_H
#define SERVERGAME_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

class ServerGame : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServerGame();
    ~ServerGame() override;

    static const int PORT;
    static const QString ADDRESS;
    static const QString ID_SLOT;
    static const QString ID_ITEM;
    static const QString QUAN;

private:
    QTcpSocket* socket = nullptr;
    QByteArray data;

    QJsonDocument doc;
    QJsonParseError parseError;

private slots:
    void incomingConnection(qintptr socketDescriptor) override;
    void sockReady();
    void sockDisc();

signals:
    void getMessage(int id_slot,int id_item,int quant);

public slots:
    bool startServer();
    void sendMessage(int id_slot,int id_item,int quant);

};

#endif // SERVERGAME_H
