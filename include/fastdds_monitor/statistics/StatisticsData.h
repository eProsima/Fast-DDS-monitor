// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Monitor.
//
// eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

/**
 * @file StatisticsData.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_STATISTICS_STATISTICSDATA_H
#define _EPROSIMA_FASTDDS_MONITOR_STATISTICS_STATISTICSDATA_H

#include <atomic>

#include <QtCore/QObject>
#include <fastdds_monitor/statistics/DataChartBox.h>

/**
 * @brief Handle all the connections between QML and the  data / real time data
 *
 * It maintains a map with key a unique id given by a static variable, and as value the
 * \c ChartBox related with this id.
 *
 * It gets with slots the QML signals sent from  data related methods.
 * Most of these methods uses the internal id to the chartbox to reference with chartbox must be affected.
 */
class StatisticsData : public QObject
{
    Q_OBJECT

public:

    StatisticsData(
            QObject* parent = nullptr);

    ~StatisticsData();

public slots:

    /**
     * Delete a series belongs to an internal Chartbox
     *
     * @warning This method is called with the QML series_index, that is not static for a series, but it is
     * an index in an array that varies. In the unlikely case of deleting two series in less time than C++
     * handles one destruction, it could lead to error
     */
    void delete_series(
            quint64 chartbox_id,
            quint64 series_index);

    //! Delete an internal Chartbox
    void delete_chartbox(
            quint64 chartbox_id);

    //! Send clear chart to internal chartbox
    void clear_charts(
            quint64 chartbox_id);

    //! Get Y max axis size
    qreal axisYMax(
            quint64 chartbox_id);
    //! Get Y min axis size
    qreal axisYMin(
            quint64 chartbox_id);
    //! Get X max axis size
    quint64 axisXMax(
            quint64 chartbox_id);
    //! Get X min axis size
    quint64 axisXMin(
            quint64 chartbox_id);

    //! Set the new Y max axis size
    void setAxisYMax(
            quint64 chartbox_id,
            qreal axisYMax);
    //! Set the new Y min axis size
    void setAxisYMin(
            quint64 chartbox_id,
            qreal axisYMin);
    //! Set the new X max axis size
    void setAxisXMax(
            quint64 chartbox_id,
            quint64 axisXMax);
    //! Set the new X min axis size
    void setAxisXMin(
            quint64 chartbox_id,
            quint64 axisXMin);
    //! Set the new X as max/min if it is bigger/lower than the current one
    void newXValue(
            quint64 chartbox_id,
            quint64 x);

    bool contains_chartbox(
            quint64 chartbox_id);

    const QVector<QPointF>& get_data(
            quint64 chartbox_id,
            quint64 series_index);

    void recalculate_y_axis(
            quint64 chartbox_id);


protected:

    /**
     * Add a new internal Chartbox
     */
    quint64 add_chartbox(
            DataChartBox* chartbox);

    //! Unique id of the new chartbox to add
    static std::atomic<quint64> last_id_;

    //! Internal chartboxes map by id
    std::map<quint64, DataChartBox*> chartboxes_;
};

#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_STATISTICSDATA_H
