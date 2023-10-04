#ifndef DBSERVICE_HPP
#define DBSERVICE_HPP

#include <QSqlDatabase>
#include <QSqlError>
#include <memory>

class DbService
{
public:
     static std::unique_ptr<DbService> create(const QString& dbfile);

    virtual ~DbService();

     bool init();
     QSqlError lastError() const { return mDb.lastError(); }

 private:
    DbService(const QString& file_name);


    QString mDbFileName;
    QSqlDatabase mDb;
};

#endif // DBSERVICE_HPP
