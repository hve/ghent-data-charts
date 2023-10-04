#include "dbservice.hpp"

DbService::DbService(const QString& file_name) : mDbFileName(file_name)
{
    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mDb.setDatabaseName(mDbFileName);
    mDb.setConnectOptions(QLatin1String("QSQLITE_OPEN_READONLY"));
}

DbService::~DbService()
{

}

std::unique_ptr<DbService> DbService::create(const QString& file_name)
{
    return std::unique_ptr<DbService>(new DbService(file_name));
}

bool DbService::init()
{
    if (mDb.isOpen())
        return true;

    if (!mDb.open())
        return false;


    // Cache basic data


    return true;
}
