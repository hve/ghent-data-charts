#ifndef BASECHARTWIDGET_HPP
#define BASECHARTWIDGET_HPP

#include <QChartView>
#include <QWidget>

// forwards
class DbService;

class BaseChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseChartWidget(DbService& dbservice, QWidget* parent = nullptr);

    void load();

protected:
    virtual bool doLoad();
    void resizeEvent(QResizeEvent*) override;
    void createDefaultChartView(QChart* chart);
    void enableSeriesForMarker(QLegendMarker *marker, bool enable);
    void setLastError(const QString& error) { mLastError = error; }

protected:
    DbService& mDbService;

private:
    QChartView* mChartView = nullptr;
    QString mLastError;
    bool mLoaded = false;
};

#endif // BASECHARTWIDGET_HPP
