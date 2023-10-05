#ifndef MODEL_HPP
#define MODEL_HPP

#include <QString>

struct District
{
    int id = -1;
    QString name;
    QString part;
};

struct CrimeCategory
{
    int id = -1;
    QString name;
};


inline bool operator==(const District& lhs, const District& rhs) { return lhs.id == rhs.id; }
inline bool operator!=(const District& lhs, const District& rhs) { return !(lhs == rhs); }

inline bool operator==(const CrimeCategory& lhs, const CrimeCategory& rhs) { return lhs.id == rhs.id; }
inline bool operator!=(const CrimeCategory& lhs, const CrimeCategory& rhs) { return !(lhs == rhs); }


#endif // MODEL_HPP