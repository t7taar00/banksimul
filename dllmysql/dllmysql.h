#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include <QString>

#include "dllmysql_global.h"
#include "mysqlconnection.h"
#include "mysqlquery.h"

class DLLMYSQLSHARED_EXPORT DLLMySQL
{

public:
    void connectDatabase();
    void closeDatabase();

    QStringList *getUserData(QString cardID, int table);

    int withdrawMoney(QString cardID, double amount);

    void lockCard(QString cardID);

private:
    MySQLConnection *dbConnect;
    MySQLQuery *dbQuery;
    QStringList *returnData;
};

#endif // DLLMYSQL_H
