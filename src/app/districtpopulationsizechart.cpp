#include "districtpopulationsizechart.hpp"
#include "dbservice.hpp"
#include <QChart>
#include <QGraphicsLayout>
#include <QGridLayout>
#include <QLegendMarker>
#include <QLineSeries>
#include <QValueAxis>

DistrictPopulationSizeChart::DistrictPopulationSizeChart(DbService& dbservice, QWidget *parent)
    : BaseChartWidget{dbservice, parent}
{
    mChart = new QChart;
    mChart->setAnimationOptions(QChart::SeriesAnimations);

    createDefaultChartView(mChart);
}

bool DistrictPopulationSizeChart::doLoad()
{
    for (auto& district : mDbService.districts()) {

        auto result = mDbService.getPopulationSeriesForDistrict(district.id);
        if (result.empty()) {
            setLastError(mDbService.lastError().text());
            return false;
        }

        auto series = new QLineSeries;
        series->setName(district.name);
        series->setVisible(true);

        for (auto& point : result)
            series->append(point.first, point.second);

        mChart->addSeries(series);
    }

    mChart->createDefaultAxes();

    // Format the X axis
    QValueAxis* axisX = reinterpret_cast<QValueAxis*>(mChart->axes(Qt::Horizontal).back());
    axisX->setRange(2000, 2023); // TODO: make dynamic
    axisX->setTickType(QValueAxis::TicksFixed);
    axisX->setTickCount(11);
    axisX->setTitleText("Jaar");
    axisX->setLabelFormat("%4i");

    // Format the Y axis
    QValueAxis* axisY = reinterpret_cast<QValueAxis*>(mChart->axes(Qt::Vertical).back());
    axisY->setRange(0, 22000);  // TODO: make dynamic
    axisY->setTickType(QValueAxis::TicksFixed);
    axisY->setTickCount(12);
    axisY->setTitleText("Aantal");
    axisY->setLabelFormat("%u");

    mChart->legend()->setVisible(true);
    mChart->legend()->setAlignment(Qt::AlignRight);

    const auto markers = mChart->legend()->markers();
    int marker_counter = 0;

    for (QLegendMarker* marker : markers) {
        QObject::connect(marker, &QLegendMarker::clicked, this, &DistrictPopulationSizeChart::onMarkerClicked);
        if (marker_counter++ < 8)
            enableSeriesForMarker(marker, true);
        else
            enableSeriesForMarker(marker, false);
    }

    return true;
}

void DistrictPopulationSizeChart::onMarkerClicked()
{
    auto marker = qobject_cast<QLegendMarker*>(sender());
    Q_ASSERT(marker);

    enableSeriesForMarker(marker, !marker->series()->isVisible());
}
