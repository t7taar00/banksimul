#include "mysqlquery.h"

MySQLQuery::MySQLQuery()
{
    query = new QSqlQuery;

    resultData = new QStringList;
}

MySQLQuery::~MySQLQuery()
{
    delete query;
    query = NULL;

    delete resultData;
    resultData = NULL;
}

void MySQLQuery::clearResultData()
{
    delete resultData;
    resultData = NULL;

    resultData = new QStringList;
}

QStringList *MySQLQuery::parseTable(QString cardID, int table)
{
    clearResultData();

    switch(table)
    {
    case 0:
        argument = "SELECT customer.name, customer.address, customer.phone FROM customer"
                   " INNER JOIN account ON customer.customer_id = account.customer_id"
                   " INNER JOIN card ON account.account_id = card.account_id"
                   " WHERE card_id = :id";
        break;
    case 1:
        argument = "SELECT account.account_id, account.customer_id, account.balance FROM account"
                   " INNER JOIN card ON account.account_id = card.account_id WHERE card_id = :id";
        break;
    case 2:
        argument = "SELECT entry.entry_id, entry.time_stamp, entry.amount FROM entry"
                   " INNER JOIN card ON entry.account_id = card.account_id WHERE card_id = :id";
        break;
    case 3:
        argument = "SELECT account_id, pin, lock_status FROM card WHERE card_id = :id";
        break;
    default:
        break;
    }

    query->prepare(argument);
    query->bindValue(":id", cardID);
    query->exec();

    while(query->next())
    {
        resultData->append(query->value(0).toString());
        resultData->append(query->value(1).toString());
        resultData->append(query->value(2).toString());
    }

    return resultData;
}

int MySQLQuery::runTransaction(QString cardID, double amount)
{
    int tempID;
    double tempBalance;

    argument = "SELECT account.account_id, account.balance FROM account"
               " INNER JOIN card ON account.account_id = card.account_id WHERE card_id = :id";

    query->prepare(argument);
    query->bindValue(":id", cardID);
    query->exec();

    while(query->next())
    {
        tempID = query->value(0).toInt();
        tempBalance = query->value(1).toDouble();
    }

    if(tempBalance - amount < 0)
    {
        return 1;
    }

    else
    {
        argument = "CALL withdraw_transaction(:id, :amount)";

        query->prepare(argument);
        query->bindValue(":id", tempID);
        query->bindValue(":amount", amount);
        query->exec();

        return 0;
    }
}

void MySQLQuery::setLockStatus(QString cardID)
{
    query->prepare("UPDATE card SET lock_status = 1 WHERE card_id = :id");
    query->bindValue(":id", cardID);
    query->exec();
}
