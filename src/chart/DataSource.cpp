#include <include/chart/DataSource.h>

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

DataSource::DataSource(QObject *parent)
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

void DataSource::update(QAbstractSeries* series)
{
    if (series) {
        QXYSeries* xySeries = static_cast<QXYSeries*>(series);
        index_++;
        if (index_ > data_.count() - 1)
            index_ = 0;

        QVector<QPointF> points = data_.at(index_);
        xySeries->replace(points);
    }
}

void DataSource::generateData(int colCount)
{
    // Remove previous data
    data_.clear();

    QVector<QPointF> points;
    points.reserve(colCount);

    QDateTime xValue;
    xValue.setDate(QDate(2016,7,3));
    xValue.setTime(QTime(0,0));
    points.append(QPointF(xValue.toMSecsSinceEpoch(), QRandomGenerator::global()->bounded(250)));
    xValue.setTime(QTime(7,0));
    points.append(QPointF(xValue.toMSecsSinceEpoch(), QRandomGenerator::global()->bounded(250)));
    xValue.setTime(QTime(9,0));
    points.append(QPointF(xValue.toMSecsSinceEpoch(), QRandomGenerator::global()->bounded(250)));
    xValue.setTime(QTime(12,0));
    points.append(QPointF(xValue.toMSecsSinceEpoch(), QRandomGenerator::global()->bounded(250)));
    xValue.setTime(QTime(14,0));
    points.append(QPointF(xValue.toMSecsSinceEpoch(), QRandomGenerator::global()->bounded(250)));
    xValue.setTime(QTime(18,0));
    points.append(QPointF(xValue.toMSecsSinceEpoch(), QRandomGenerator::global()->bounded(250)));
    xValue.setTime(QTime(21,0));
    points.append(QPointF(xValue.toMSecsSinceEpoch(), QRandomGenerator::global()->bounded(250)));
    xValue.setTime(QTime(23,30));
    points.append(QPointF(xValue.toMSecsSinceEpoch(), QRandomGenerator::global()->bounded(250)));
    xValue.setDate(QDate(2016,7,4));

    data_.append(points);

    for (QVector<QPointF>& d : data_)
    {
        qDebug() << "------------------------------------------------";
        for (QPointF p : d)
        {
            qDebug() << "x: " << p.x() << "\t| y: " << p.y();
        }
        qDebug() << "------------------------------------------------";
    }

    axisYMax_ = 300;
    axisYMin_ = 0;
    QDateTime startDate(QDate(2016, 7, 3), QTime(0, 0, 0));
    QDateTime endDate(QDate(2016, 7, 4), QTime(0, 0, 0));
    axisXMax_ = endDate.toMSecsSinceEpoch();
    axisXMin_ = startDate.toMSecsSinceEpoch();
}
