#ifndef SERVERGAME_H
#define SERVERGAME_H

#include "network/network.h"


class ServerGame : public Network
{
    Q_OBJECT
public:
    explicit ServerGame();
    ~ServerGame() override;

private slots:
    void incomingConnection(qintptr socketDescriptor) override;

public slots:
    bool start() override;

};

#endif // SERVERGAME_H
