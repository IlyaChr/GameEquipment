#include "clientgame.h"
#include "servergame.h"

ClientGame::ClientGame()
{
    socket = new QTcpSocket(this);
    connect(socket,&QTcpSocket::readyRead,this,&ClientGame::sockReady);
    connect(socket,&QTcpSocket::disconnected,this,&ClientGame::sockDisk);
}

ClientGame::~ClientGame()
{}

void ClientGame::sockReady()
{
    if (socket->waitForConnected(500)){

        socket->waitForReadyRead(500);

        data = socket->readAll();

        doc = QJsonDocument::fromJson(data,&parseError);

        if (parseError.errorString().toInt() == QJsonParseError::NoError){

            int id_slot;
            int id_item;
            int quant;

            id_slot = doc.object().value(ServerGame::ID_SLOT).toInt();
            id_item = doc.object().value(ServerGame::ID_ITEM).toInt();
            quant = doc.object().value(ServerGame::QUAN).toInt();

            //qDebug()<<id_slot<<":"<<id_item<<":"<<quant<<" - mes from server";

            emit getMessage(id_slot,id_item,quant);


        }else {

            qDebug()<<"Ошибки с форматом данных на клиенте:"<<parseError.errorString();
        }
    }

}

bool ClientGame::connectToServer()
{
    socket->connectToHost(ServerGame::ADDRESS,static_cast<unsigned short>(ServerGame::PORT));
    if (socket->waitForConnected(500)){
        if (socket->state() == QTcpSocket::ConnectedState){
            qDebug()<<"Connection to host is established";
            return true;
        }
    }

    qDebug()<<"Connection to host failed";
    return false;
}

void ClientGame::sendMessage(int id_slot, int id_item, int quant)
{
    if (!socket){
        return;
    }

    //json
    QString message = QString("{"
                    "\"%1\":%2,"
                    "\"%3\":%4,"
                    "\"%5\":%6"
                    "}").arg(ServerGame::ID_SLOT,QString::number(id_slot),ServerGame::ID_ITEM,QString::number(id_item),ServerGame::QUAN,QString::number(quant));

    socket->write(message.toStdString().c_str());
    qDebug()<<"Mes to server sended"<<endl;
}


void ClientGame::sockDisk()
{
    if (socket){
        qDebug()<<"Client is disconnected";
        socket->deleteLater();
    }
}
