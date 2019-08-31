#ifndef NETWORK_H
#define NETWORK_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>


class Network : public QTcpServer
{
    Q_OBJECT
public:
    explicit Network();
    ~Network();

protected:

    static const int PORT;
    static const QString ADDRESS;
    static const QString ID_SLOT;
    static const QString ID_ITEM;
    static const QString QUAN;

    QTcpSocket* socket = nullptr;
    QByteArray data;

    QJsonDocument doc;
    QJsonParseError parseError;

public slots:
    void sockReady();
    void sockDisc();
    bool parseFromJson(const QByteArray& array);
    void sendMessage(int id_slot,int id_item,int quant);
    virtual bool start() = 0;

signals:
    void getMessage(int id_slot,int id_item,int quant);
};


#endif // NETWORK_H
