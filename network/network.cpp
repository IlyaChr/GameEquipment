#include "network.h"

const int Network::PORT=5555;
const QString Network::ADDRESS="127.0.0.1";
const QString Network::ID_SLOT="id_slot";
const QString Network::ID_ITEM="id_item";
const QString Network::QUAN="quan";


Network::Network()
{}

Network::~Network()
{}

void Network::sockReady()
{
    if (socket->waitForConnected(10)){

        socket->waitForReadyRead(10);

        QList<QString> dataList;

        while (!socket->atEnd()){
            dataList.push_back(QString::fromStdString(socket->readLine().toStdString()).trimmed());
        }

        for ( const auto& value : dataList){
            parseFromJson(value.toUtf8());
        }
    }

}


void Network::sendMessage(int id_slot, int id_item, int quant)
{
    if (!socket || (socket->state() != QTcpSocket::ConnectedState)){
        return;
    }



    //json
    QString message = QString("{"
                    "\"%1\":%2,"
                    "\"%3\":%4,"
                    "\"%5\":%6"
                    "}").arg(Network::ID_SLOT,QString::number(id_slot),Network::ID_ITEM,QString::number(id_item),Network::QUAN,QString::number(quant));

    socket->write(message.toStdString().c_str());
    socket->write("\n");
    //qDebug()<<"Message sended"<<endl;
}


void Network::sockDisc()
{
    if (socket){
        qDebug()<<"disconnecting";
        socket->close();
        socket->deleteLater();
    }
}

bool Network::parseFromJson(const QByteArray &array)
{

    doc = QJsonDocument::fromJson(array,&parseError);

    if (!doc.isNull()){

        int id_slot;
        int id_item;
        int quant;

        id_slot = doc.object().value(Network::ID_SLOT).toInt();
        id_item = doc.object().value(Network::ID_ITEM).toInt();
        quant = doc.object().value(Network::QUAN).toInt();

        emit getMessage(id_slot,id_item,quant);
        return true;

    }else {

        qDebug()<<"Ошибки с форматом данных:"<<parseError.errorString();
    }

    return false;
}
