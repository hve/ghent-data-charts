#include "mainwidget.hpp"
#include "citypopulationchart.hpp"
#include "dbservice.hpp"
#include "basechartwidget.hpp"
#include "districtpopulationdensitychart.hpp"
#include "districtpopulationsizechart.hpp"

#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QStringListModel>

MainWidget::MainWidget(DbService& dbservice, QWidget *parent)
    : QWidget{parent},
      mDbService(dbservice),
      mChartSelection(new QComboBox(this)),
      mContentArea(new QWidget(this))
{
    mContentArea->installEventFilter(this);

    setMinimumSize(800, 400);
    resize(1200, 600);

    mChartSelection->addItem("Totale bevolkingsaantal evolutie", CityPopulation);
    mChartSelection->addItem("Stadswijk bevolkingsaantal evolutie", DistrictPopulationSize);
    mChartSelection->addItem("Stadswijk bevolkingsdichtheid evolutie", DistrictPopulationDensity);

    auto top_layout = new QHBoxLayout;
    top_layout->addWidget(new QLabel("Grafiek:"));
    top_layout->addWidget(mChartSelection);
    top_layout->addStretch(1);

    auto main_layout =  new QVBoxLayout;
    main_layout->addLayout(top_layout);
    main_layout->addWidget(mContentArea);
    setLayout(main_layout);

    setActiveChart(CityPopulation);

    setMouseTracking(true);

    connect(mChartSelection, &QComboBox::currentIndexChanged, this, &MainWidget::onChartSelectionChanged);

    qApp->setApplicationDisplayName(tr("Gent in grafieken"));
}

void MainWidget::setActiveChart(ChartType chart)
{
    if (mActiveChartWidget) {
        mActiveChartWidget->setVisible(false);
        mActiveChartWidget->deleteLater();
    }

    switch (chart) {
    case CityPopulation: mActiveChartWidget = new CityPopulationChart(mDbService, mContentArea); break;
    case DistrictPopulationSize: mActiveChartWidget = new DistrictPopulationSizeChart(mDbService, mContentArea); break;
    case DistrictPopulationDensity: mActiveChartWidget = new DistrictPopulationDensityChart(mDbService, mContentArea); break;
    default: break;
    }

    mActiveChartWidget->load();
    mActiveChartWidget->resize(mContentArea->size());
    mActiveChartWidget->setVisible(true);
}

void MainWidget::onChartSelectionChanged(int index)
{
    setActiveChart(static_cast<ChartType>(index));
}

bool MainWidget::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::Resize && object == mContentArea && mActiveChartWidget)
        mActiveChartWidget->resize(mContentArea->size());

    return QObject::eventFilter(object, event);
}
