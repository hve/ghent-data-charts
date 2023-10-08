#ifndef DBSERVICE_HPP
#define DBSERVICE_HPP

#include <QSqlDatabase>
#include <QSqlError>
#include <QHash>
#include <QVector>
#include <memory>
#include "model.hpp"

class DbService
{
public:
     static std::unique_ptr<DbService> create(const QString& dbfile);

    virtual ~DbService();

     bool init();
     QSqlError lastError() const { return mLastError; }

     const QVector<District>& districts() const { return mDistricts; }
     const QVector<CrimeCategory>& crimeCategories() const { return mCrimeCategories; }

     District findDistrictById(int id) const;
     District findDistrictByName(const QString& name) const;
     CrimeCategory findCrimeCategoryById(int id) const;
     CrimeCategory findCrimeCategoryByName(const QString& name) const;

     QVector<QPair<int, int>> getPopulationSeries();
     QVector<QPair<int, int>> getPopulationSeriesForDistrict(int district_id);
     QVector<QPair<int, double>> getPopulationDensitySeriesForDistrict(int district_id);

 private:
     bool loadDistricts();
     bool loadCrimeCategories();

 private:
    DbService(const QString& file_name);

    QString mDbFileName;
    QSqlDatabase mDb;
    QSqlError mLastError;

    QVector<District> mDistricts;
    QHash<int, District> mDistrictIdMap;
    QVector<CrimeCategory> mCrimeCategories;
    QHash<int, CrimeCategory> mCrimeCategoryIdMap;
};

#endif // DBSERVICE_HPP
