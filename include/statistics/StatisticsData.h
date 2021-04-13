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
    Q_PROPERTY(quint64 axisXMax READ axisXMax NOTIFY axisXMaxChanged)
    Q_PROPERTY(quint64 axisXMin READ axisXMin NOTIFY axisXMinChanged)

public:

    explicit StatisticsData(
            QObject *parent = 0);


    void setData(const QList<QVector<QPointF>>& data);
    void appendData(const QVector<QPointF>& dataSeries);
    void clear();

    qreal axisYMax();
    qreal axisYMin();
    quint64 axisXMax();
    quint64 axisXMin();

    void setAxisYMax(qreal axisYMax);
    void setAxisYMin(qreal axisYMin);
    void setAxisXMax(quint64 axisXMax);
    void setAxisXMin(quint64 axisXMin);

Q_SIGNALS:

public slots:

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
    quint64 axisXMax_;
    quint64 axisXMin_;
};


#endif // STATISTICSDATA_H
