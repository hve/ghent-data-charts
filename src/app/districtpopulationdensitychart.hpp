// SPDX-License-Identifier: GPL-3.0-only

#ifndef DISTRICTPOPULATIONDENSITYCHART_HPP
#define DISTRICTPOPULATIONDENSITYCHART_HPP

#include "basechartwidget.hpp"

class DistrictPopulationDensityChart : public BaseChartWidget
{
    Q_OBJECT
public:
    explicit DistrictPopulationDensityChart(DbService& dbservice, QWidget *parent = nullptr);

protected:
    bool doLoad() override;
    void onMarkerClicked();

private:
    QChart* mChart = nullptr;
};

#endif // DISTRICTPOPULATIONDENSITYCHART_HPP
