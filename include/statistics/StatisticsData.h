#ifndef STATISTICSDATA_H
#define STATISTICSDATA_H

#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class StatisticsData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal axisYMax READ axisYMax NOTIFY axisYMaxChanged)
    Q_PROPERTY(qreal axisYMin READ axisYMin NOTIFY axisYMinChanged)
    Q_PROPERTY(qreal axisXMax READ axisXMax NOTIFY axisXMaxChanged)
    Q_PROPERTY(qreal axisXMin READ axisXMin NOTIFY axisXMinChanged)

public:

    explicit StatisticsData(
            QObject *parent = 0);

    qreal axisYMax()
    {
        return axisYMax_;
    }

    qreal axisYMin()
    {
        return axisYMin_;
    }

    qreal axisXMax()
    {
        return axisXMax_;
    }

    qreal axisXMin()
    {
        return axisXMin_;
    }

Q_SIGNALS:

public slots:

    void generateData(
            int colCount);

    void update(
            QAbstractSeries* series);

signals:
    void axisYMaxChanged();
    void axisYMinChanged();
    void axisXMaxChanged();
    void axisXMinChanged();

private:
    QList<QVector<QPointF>> data_;
    int index_;
    qreal axisYMax_;
    qreal axisYMin_;
    qreal axisXMax_;
    qreal axisXMin_;
};


#endif // STATISTICSDATA_H
