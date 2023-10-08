#ifndef DISTRICTPOPULATIONSIZECHART_HPP
#define DISTRICTPOPULATIONSIZECHART_HPP

#include "basechartwidget.hpp"

class DistrictPopulationSizeChart : public BaseChartWidget
{
    Q_OBJECT
public:
    explicit DistrictPopulationSizeChart(DbService& dbservice, QWidget *parent = nullptr);

protected:
    bool doLoad() override;
    void onMarkerClicked();

private:
    QChart* mChart = nullptr;
};

#endif // DISTRICTPOPULATIONSIZECHART_HPP
