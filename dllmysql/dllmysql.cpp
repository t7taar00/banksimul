#include "dllmysql.h"

void DLLMySQL::connectDatabase()
{
    dbConnect = new MySQLConnection;
    dbConnect->openConnection();

    dbQuery = new MySQLQuery;

    returnData = new QStringList;
}

void DLLMySQL::closeDatabase()
{
    dbConnect->closeConnection();

    delete dbConnect;
    dbConnect = NULL;

    delete dbQuery;
    dbQuery = NULL;

    delete returnData;
    returnData = NULL;
}

QStringList *DLLMySQL::getUserData(QString cardID, int table)
{
    /* Table-indexin arvot:
     * 0 = Customer, asiakastiedot
     * 1 = Account, tilitiedot
     * 2 = Entry, tilimerkinnät
     * 3 = Card, kortti ja kirjautumistiedot
     *
     * Datan järjestys:
     * Customer-taulusta
     *  0. nimi 1. osoite 2. puhelin
     * Account-taulusta
     *  0. tiliID 1. asiakasID 2. saldo
     * Entry-taulusta
     *  0. entryID 1. aika 2. määrä, toistuu...
     * Card-taulusta
     *  0. tiliID 1. pin 2. lukitus */

    returnData = dbQuery->parseTable(cardID, table);

    // Palautusdatan indeksien käsittely ja tulostus:
    for(int i = 0; i < returnData->size(); i++)
    {
        qDebug() << returnData->at(i);
    }

    return returnData;
}

int DLLMySQL::withdrawMoney(QString cardID, double amount)
{
    int returnValue = dbQuery->runTransaction(cardID, amount);

    return returnValue;
}

void DLLMySQL::lockCard(QString cardID)
{
    dbQuery->setLockStatus(cardID);
}
