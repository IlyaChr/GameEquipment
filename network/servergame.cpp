#include "servergame.h"


ServerGame::ServerGame():
    Network ()
{}

ServerGame::~ServerGame()
{}


bool ServerGame::start()
{
    if (this->listen(QHostAddress::Any,static_cast<unsigned short>(PORT))){
        qDebug()<<"Server is running!";
        return true;
    }else {
        qDebug()<<"Running server failed";
        return false;
    }
}


void ServerGame::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,&QTcpSocket::readyRead,this,&Network::sockReady);
    connect(socket,&QTcpSocket::disconnected,this,&Network::sockDisc);

    qDebug()<<"Client connected socketDescriptor: "<<socketDescriptor<<endl;

}





