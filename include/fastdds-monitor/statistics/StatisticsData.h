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

    //! Default QObject constructor
    explicit StatisticsData(
            QObject* parent = 0);

    //! Set data of the chart
    void setData(
            const QList<QVector<QPointF>>& data);

    //! Add data serie to the chart
    void appendData(
            const QVector<QPointF>& dataSeries);

    //! Erase data of the chart
    void clear();

    //! Get Y max axis size
    qreal axisYMax();
    //! Get Y min axis size
    qreal axisYMin();
    //! Get X max axis size
    quint64 axisXMax();
    //! Get X min axis size
    quint64 axisXMin();

    //! Set the new Y max axis size
    void setAxisYMax(
            qreal axisYMax);
    //! Set the new Y min axis size
    void setAxisYMin(
            qreal axisYMin);
    //! Set the new X max axis size
    void setAxisXMax(
            quint64 axisXMax);
    //! Set the new X min axis size
    void setAxisXMin(
            quint64 axisXMin);

public slots:

    //! Receives the signal when data has been updated
    void update(
            QAbstractSeries* series);

signals:

    //! Signal to communicate that max Y axis has changed
    void axisYMaxChanged();
    //! Signal to communicate that min Y axis has changed
    void axisYMinChanged();
    //! Signal to communicate that max X axis has changed
    void axisXMaxChanged();
    //! Signal to communicate that min X axis has changed
    void axisXMinChanged();

private:

    //! TODO
    QList<QVector<QPointF>> data_;

    //! TODO
    int index_;

    //! Max Y axis size
    qreal axisYMax_;

    //! Min Y axis size
    qreal axisYMin_;

    //! Max X axis size
    quint64 axisXMax_;

    //! Min X axis size
    quint64 axisXMin_;
};


#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_STATISTICSDATA_H
