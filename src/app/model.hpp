// SPDX-License-Identifier: GPL-3.0-only

#ifndef MODEL_HPP
#define MODEL_HPP

#include <QString>

struct District
{
    int id = -1;
    QString name;
    QString part;
    double area_km2 = 0.0f;
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
