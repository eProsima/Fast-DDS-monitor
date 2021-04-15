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

/**
 * @file StatisticsData.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_STATISTICS_STATISTICSDATA_H
#define _EPROSIMA_FASTDDS_MONITOR_STATISTICS_STATISTICSDATA_H

#include <QtCharts/QAbstractSeries>
#include <QtCore/QObject>

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

//! TODO
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


#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_STATISTICSDATA_H
