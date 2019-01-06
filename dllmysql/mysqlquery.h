#ifndef MYSQLQUERY_H
#define MYSQLQUERY_H

#include <QDebug>
#include <QString>
#include <QSqlQuery>

class MySQLQuery
{
public:
    MySQLQuery();
    ~MySQLQuery();

    void clearResultData();

    QStringList* parseTable(QString cardID, int table);

    int runTransaction(QString cardID, double amount);

    void setLockStatus(QString cardID);

private:
    QString argument;

    QSqlQuery *query;
    QStringList *resultData;
};

#endif // MYSQLQUERY_H
