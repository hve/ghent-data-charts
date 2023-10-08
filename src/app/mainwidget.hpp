#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include <QComboBox>
#include <QWidget>

// forwards
class DbService;
class BaseChartWidget;
class CheckComboBox;
class QLegendMarker;
class QListView;
class QStringListModel;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(DbService& dbservice, QWidget *parent = nullptr);

    enum ChartType {
        CityPopulation = 0,
        DistrictPopulationSize,
        DistrictPopulationDensity
    };

    void setActiveChart(ChartType chart);

public slots:
    void onChartSelectionChanged(int index);

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    DbService& mDbService;

    QComboBox* mChartSelection = nullptr;
    QWidget* mContentArea = nullptr;
    BaseChartWidget* mActiveChartWidget = nullptr;
};

#endif // MAINWIDGET_HPP
