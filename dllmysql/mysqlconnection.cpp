#include "mysqlconnection.h"

void MySQLConnection::openConnection()
{
    qDebug() << "Setting up connection information...";

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("***");
    db.setDatabaseName("***");
    db.setUserName("***");
    db.setPassword("***");

    qDebug() << "Opening connection...";

    if(db.open())
    {
        qDebug() << "Connection success!";
        qDebug() << db.connectionName();
    }
    else
    {
        qDebug() << "Connection failed!";
    }
}

void MySQLConnection::closeConnection()
{
    qDebug() << "Closing connection...";

    db.close();
    db.removeDatabase(db.connectionName());
}
