#ifndef CITYPOPULATIONCHART_HPP
#define CITYPOPULATIONCHART_HPP

#include "basechartwidget.hpp"

class CityPopulationChart : public BaseChartWidget
{
    Q_OBJECT
public:
    explicit CityPopulationChart(DbService& dbservice, QWidget* parent = nullptr);

protected:
    bool doLoad() override;

private:
    QChart* mChart = nullptr;
};

#endif // CITYPOPULATIONCHART_HPP
