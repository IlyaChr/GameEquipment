#include "servergame.h"

const int ServerGame::PORT=5555;
const QString ServerGame::ADDRESS="127.0.0.1";
const QString ServerGame::ID_SLOT="id_slot";
const QString ServerGame::ID_ITEM="id_item";
const QString ServerGame::QUAN="quan";




ServerGame::ServerGame()
{}

ServerGame::~ServerGame()
{}

bool ServerGame::startServer()
{
    if (this->listen(QHostAddress::Any,PORT)){
        qDebug()<<"Server is running!";
        return true;
    }else {
        qDebug()<<"Running server failed";
        return false;
    }
}

void ServerGame::sendMessage(int id_slot, int id_item, int quant)
{
    if (!socket){
        return;
    }


    qDebug()<<id_slot<<":"<<id_item<<":"<<quant<<" - mes to client";

    //json
    QString message = QString("{"
                    "\"%1\":%2,"
                    "\"%3\":%4,"
                    "\"%5\":%6"
                    "}").arg(ID_SLOT,QString::number(id_slot),ID_ITEM,QString::number(id_item),QUAN,QString::number(quant));

    socket->write(message.toStdString().c_str());
    socket->write("\n");
    qDebug()<<"Mes to client sended"<<endl;
}

void ServerGame::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,&QTcpSocket::readyRead,this,&ServerGame::sockReady);
    connect(socket,&QTcpSocket::disconnected,this,&ServerGame::sockDisc);

    qDebug()<<"Client connected socketDescriptor: "<<socketDescriptor<<endl;

}

void ServerGame::sockReady()
{
    if (socket->waitForConnected(500)){

        socket->waitForReadyRead(500);

        //data = socket->readAll();
        QList<QString> dataList;

        while (!socket->atEnd()){
            dataList.push_back(QString::fromStdString(socket->readLine().toStdString()).trimmed());
        }

        for ( const auto& value : dataList){
            parseFromJson(value.toUtf8());
        }
    }
}

void ServerGame::sockDisc()
{
    if (socket){
        qDebug()<<"Server is Closed";
        socket->close();
        socket->deleteLater();
    }

}

bool ServerGame::parseFromJson(const QByteArray &array)
{
    doc = QJsonDocument::fromJson(array,&parseError);

    if (!doc.isNull()){

        int id_slot;
        int id_item;
        int quant;

        id_slot = doc.object().value(ServerGame::ID_SLOT).toInt();
        id_item = doc.object().value(ServerGame::ID_ITEM).toInt();
        quant = doc.object().value(ServerGame::QUAN).toInt();

        //qDebug()<<id_slot<<":"<<id_item<<":"<<quant<<" - mes from server";

        emit getMessage(id_slot,id_item,quant);
        return true;

    }else {

        qDebug()<<"Ошибки с форматом данных на клиенте:"<<parseError.errorString();
    }

    return false;
}
