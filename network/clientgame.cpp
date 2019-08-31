#include "clientgame.h"

ClientGame::ClientGame()
{
    socket = new QTcpSocket(this);
    connect(socket,&QTcpSocket::readyRead,this,&Network::sockReady);
    connect(socket,&QTcpSocket::disconnected,this,&Network::sockDisc);
}

ClientGame::~ClientGame()
{}

bool ClientGame::start()
{
    socket->connectToHost(ADDRESS,static_cast<unsigned short>(PORT));
    if (socket->waitForConnected(100)){
        if (socket->state() == QTcpSocket::ConnectedState){
            qDebug()<<"Connection to host is established";
            return true;
        }
    }

    qDebug()<<"Connection to host failed";
    return false;
}



