#ifndef CLIENTGAME_H
#define CLIENTGAME_H

#include "network/network.h"

class ClientGame : public Network
{
    Q_OBJECT
public:
    explicit ClientGame();
    ~ClientGame() override;

public slots:
    bool start() override;

};

#endif // CLIENTGAME_H
