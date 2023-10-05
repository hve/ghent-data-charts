#include "dbservice.hpp"
#include <QSqlQuery>

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

    if (!mDb.open()) {
        mLastError = mDb.lastError();
        return false;
    }


    // Cache basic data

    if (!loadDistricts())
        return false;

    if (!loadCrimeCategories())
        return false;

    return true;
}

District DbService::findDistrictById(int id) const
{
    auto it = mDistrictIdMap.find(id);
    if (it != mDistrictIdMap.end())
        return it.value();
    return District{};
}

District DbService::findDistrictByName(const QString& name) const
{
    auto it = std::find_if(mDistricts.begin(), mDistricts.end(), [name](const District& district) { return name == district.name;});
    if (it != mDistricts.end())
        return *it;
    return District{};
}

CrimeCategory DbService::findCrimeCategoryById(int id) const
{
    auto it = mCrimeCategoryIdMap.find(id);
    if (it != mCrimeCategoryIdMap.end())
        return it.value();
    return CrimeCategory{};
}

CrimeCategory DbService::findCrimeCategoryByName(const QString &name) const
{
    auto it = std::find_if(mCrimeCategories.begin(), mCrimeCategories.end(), [name](const CrimeCategory& category) { return name == category.name;});
    if (it != mCrimeCategories.end())
        return *it;
    return CrimeCategory{};
}

bool DbService::loadDistricts()
{
    auto sql = "select stadswijk_id, stadswijk_naam, stadsdeel from stadswijk order by stadswijk_naam";

    QSqlQuery query(mDb);

    if (!query.exec(sql)) {
        mLastError = query.lastError();
        return false;
    }

    while (query.next()) {
        District district;

        district.id = query.value(0).toInt();
        district.name = query.value(1).toString();
        district.part = query.value(2).toString();

        mDistricts.append(district);
        mDistrictIdMap.insert(district.id, district);
    }

    qDebug() << "Loaded " << mDistricts.size() << " city districts";

    return true;
}

bool DbService::loadCrimeCategories()
{
    auto sql = "select misdrijf_categorie_id, misdrijf_categorie_naam from misdrijf_categorie order by misdrijf_categorie_naam";

    QSqlQuery query(mDb);

    if (!query.exec(sql)) {
        mLastError = query.lastError();
        return false;
    }

    while (query.next()) {
        CrimeCategory category;

        category.id = query.value(0).toInt();
        category.name = query.value(1).toString();

        mCrimeCategories.append(category);
        mCrimeCategoryIdMap.insert(category.id, category);
    }

    qDebug() << "Loaded " << mCrimeCategories.size() << " crime categories";

    return true;
}
