#include <include/statistics/StatisticsData.h>

#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QCategoryAxis>
#include <QDateTime>

#include <QDebug>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries*)
Q_DECLARE_METATYPE(QAbstractAxis*)

StatisticsData::StatisticsData(QObject *parent)
    : QObject(parent)
    , index_(-1)
    , axisYMax_(10)
    , axisYMin_(0)
    , axisXMax_(10)
    , axisXMin_(0)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();
}

void StatisticsData::setData(const QList<QVector<QPointF>> &data)
{
    data_.clear();
    data_.append(data);
}

void StatisticsData::appendData(const QVector<QPointF>& dataSeries)
{
    data_.append(dataSeries);
}


void StatisticsData::clear()
{
    data_.clear();
}

qreal StatisticsData::axisYMax()
{
    return axisYMax_;
}

qreal StatisticsData::axisYMin()
{
    return axisYMin_;
}

quint64 StatisticsData::axisXMax()
{
    return axisXMax_;
}

quint64 StatisticsData::axisXMin()
{
    return axisXMin_;
}

void StatisticsData::setAxisYMax(qreal axisYMax)
{
    axisYMax_ = axisYMax;
}

void StatisticsData::setAxisYMin(qreal axisYMin)
{
    axisYMin_ = axisYMin;
}

void StatisticsData::setAxisXMax(quint64 axisXMax)
{
    axisXMax_ = axisXMax;
}

void StatisticsData::setAxisXMin(quint64 axisXMin)
{
    axisXMin_ = axisXMin;
}

void StatisticsData::update(QAbstractSeries* series)
{
    if (series)
    {
        QXYSeries* xySeries = static_cast<QXYSeries*>(series);
        index_++;
        if (index_ > data_.count() - 1)
        {
            index_ = 0;
        }

        QVector<QPointF> points = data_.at(index_);
        xySeries->replace(points);
    }
}
