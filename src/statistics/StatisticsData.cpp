// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <QDateTime>
#include <QDebug>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QXYSeries>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>

#include <include/statistics/StatisticsData.h>

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
