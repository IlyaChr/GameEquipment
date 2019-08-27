#ifndef DB_H
#define DB_H

#include <QObject>
#include <QMap>


class Db
{
public:
    static Db& Instance(){
        static Db instance;
        return instance;
    }

    QMap<int, int> loadData(int id_item);

    bool saveData(int id_slot,int id_item,int new_quant);

private:
    Db();
    ~Db();
    Db(const Db& copy) = delete;
    Db& operator=(const Db&) = delete;

    static QString DATABASE_PATH;
};

#endif // DB_H
