// SPDX-License-Identifier: GPL-3.0-only

#include "citypopulationchart.hpp"

#include "dbservice.hpp"
#include <QChart>
#include <QGraphicsLayout>
#include <QGridLayout>
#include <QLegendMarker>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QBarCategoryAxis>

CityPopulationChart::CityPopulationChart(DbService& dbservice, QWidget* parent)
    : BaseChartWidget{dbservice, parent}
{
    mChart = new QChart;
    mChart->setAnimationOptions(QChart::SeriesAnimations);

    createDefaultChartView(mChart);
}

bool CityPopulationChart::doLoad()
{
    auto result = mDbService.getPopulationSeries();
    if (result.empty()) {
        setLastError(mDbService.lastError().text());
        return false;
    }

    QStringList yearCategories;
    auto series = new QBarSeries;
    auto set = new QBarSet("Totale bevolking");

    for (auto& point : result) {
        yearCategories.append(QString("%1").arg(point.first));
        set->append(point.second);
    }

    series->append(set);
    mChart->addSeries(series);

    // Format the X axis
    auto axisX = new QBarCategoryAxis;
    axisX->append(yearCategories);
    mChart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Format the Y axis
    auto axisY = new QValueAxis;
    axisY->setRange(190000, 300000);    // TODO: make dynamic
    axisY->setTickType(QValueAxis::TicksFixed);
    axisY->setTickCount(12);
    axisY->setLabelFormat("%u");
    mChart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // No need for legend
    mChart->legend()->setVisible(false);

    return true;
}
