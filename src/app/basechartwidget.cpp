#include "basechartwidget.hpp"

#include <QLabel>
#include <QVBoxLayout>
#include <QLegendMarker>

BaseChartWidget::BaseChartWidget(DbService& dbservice, QWidget* parent)
    : QWidget{parent}, mDbService(dbservice)
{
}

void BaseChartWidget::load()
{
    if (mLoaded || layout())
        return;

    if (!doLoad()) {
        auto errorLabel = new QLabel(this);
        auto errorLayout = new QVBoxLayout(this);
        errorLabel->setText(tr("Error loading chart:\n%1").arg(mLastError));
        QFont font = errorLabel->font();
        font.setPointSize(20);
        errorLabel->setFont(font);
        errorLabel->setAlignment(Qt::AlignCenter);
        errorLayout->addWidget(errorLabel);
        setLayout(errorLayout);
    }

    mLoaded = true;
}

bool BaseChartWidget::doLoad()
{
    return true;
}

void BaseChartWidget::resizeEvent(QResizeEvent*)
{
    if (mChartView)
        mChartView->resize(size());
}

void BaseChartWidget::createDefaultChartView(QChart* chart)
{
    Q_ASSERT(mChartView == nullptr);

    mChartView = new QChartView(chart, this);
    mChartView->setRenderHint(QPainter::Antialiasing);
}

void BaseChartWidget::enableSeriesForMarker(QLegendMarker *marker, bool enable)
{
    Q_ASSERT(marker);

    marker->series()->setVisible(enable);
    marker->setVisible(true);

    // Dim marker when series is not visible
    qreal alpha = 1.0;
    if (!enable)
        alpha = 0.5;

    QColor color;
    QBrush brush = marker->labelBrush();
    color = brush.color();
    color.setAlphaF(alpha);
    brush.setColor(color);
    marker->setLabelBrush(brush);

    brush = marker->brush();
    color = brush.color();
    color.setAlphaF(alpha);
    brush.setColor(color);
    marker->setBrush(brush);

    QPen pen = marker->pen();
    color = pen.color();
    color.setAlphaF(alpha);
    pen.setColor(color);
    marker->setPen(pen);
}
