#include "db.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStandardPaths>

//for future better way to contain db files in windows folder
//in this project we using applicationDirPath for simplicity
//QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)

/**
 * @brief Db::loadData
 * @param id_item
 * @return
 */
QMap<int, int> Db::loadData(int id_item)
{

    QSqlDatabase db = QSqlDatabase::database();
    QMap<int,int> value;

    QSqlQuery query(db);
    query.exec(QString("select slot_id , quan  from inventory "
               "where item_id = %1 ").arg(id_item));

    int slot_id,quan;


    while (query.next()) {
        slot_id = query.value("slot_id").toInt();
        quan = query.value("quan").toInt();
        value.insert(slot_id,quan);
    }

    return value;

}

/**
 * @brief Db::saveData
 * @param id_slot
 * @param id_item
 * @param new_quant
 */
bool Db::saveData(int id_slot, int id_item, int quan)
{
    QSqlDatabase db = QSqlDatabase::database();

    QSqlQuery query(db);

    db.transaction();

    query.prepare("update inventory "
                  "set quan  = :quan "
                  "where item_id = :item_id and slot_id = :slot_id ");

    query.bindValue(":quan", quan);
    query.bindValue(":item_id", id_item);
    query.bindValue(":slot_id", id_slot);


    query.exec();

    query.clear();
    return db.commit();
}


Db::Db()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_PATH);


    if (!db.open()){
        qDebug()<<"faild to open database"<<endl;
    }else {

        qDebug()<<"Connection to Db"<<endl;
    }
}

/**
 * @brief Db::~Db
 * close connection
 */
Db::~Db()
{
    QSqlDatabase db = QSqlDatabase::database();

    db.close();

    qDebug()<<"Connection to db has closed"<<endl;
}
