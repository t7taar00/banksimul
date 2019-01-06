#ifndef MYSQLCONNECTION_H
#define MYSQLCONNECTION_H

#include <QDebug>
#include <QtSql>

class MySQLConnection
{
public:
    void openConnection();
    void closeConnection();

private:
    QSqlDatabase db;
};

#endif // MYSQLCONNECTION_H
