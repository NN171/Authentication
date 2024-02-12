#include "databaseconnection.h"
#include <qdebug.h>

DatabaseConnection::DatabaseConnection()
{
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("C:/Users/Admin/Documents/Login/log.db");
}

bool DatabaseConnection::Connect()
{
    if (dataBase.open())
        return true;
    else return false;
}

void DatabaseConnection::Disconnect()
{
    dataBase.close();
}
