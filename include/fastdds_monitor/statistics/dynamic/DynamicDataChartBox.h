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
 * @file DynamicDataChartBox.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICCHARTBOX_H
#define _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICCHARTBOX_H

#include <limits>
#include <mutex>

#include <QtCharts/QVXYModelMapper>

#include <fastdds_monitor/statistics/DataChartBox.h>
#include <fastdds_monitor/model/model_types.h>

struct UpdateParameters
{
    QString data_kind;
    quint64 time_from;
    std::vector<QString> source_ids;
    std::vector<QString> target_ids;
    std::vector<QString> statistics_kinds;
    std::vector<quint64> series_ids;
    /**
     * This indicates that the statistics are calculated cumulatively, i.e. each data point is calculated with
     * the current timestamp minus the cumulative time interval as initial time, and with the current timestamp as
     * final time.
     */
    std::vector<bool> cumulative;
    std::vector<quint64> cumulative_interval;
};

/**
 * @brief Class that represets a ChartBox with dynamic data
 *
 * In QML DynamicStatisticsChartView is a panel that can represent 0 or several series at the same time,
 * all of them with the same update time and statistics_kind.
 * These series will get 1 (or all in NONE case) new data each update interval, and will add it to internal
 * series in \c DataModel objects stored in a vector.
 *
 * The internal series information is stored in the variable \c current_update_parameters_ and it should be
 * updated every time a series is added or deleted.
 *
 * This map uses a unique id to represent each series, and this index is stored in the vector \c series_ids
 * with the order of the creation of each series!
 * Be aware that this id is not the same as \c seriesIndex from QML that is used in \c delete_series_by_index
 * as QML does not mantain a unique inmutable id for each series.
 */
class DynamicDataChartBox : public DataChartBox
{

public:

    DynamicDataChartBox(
            QString data_kind,
            quint64 time_to,
            quint64 window_size,
            quint64 max_points = 0,
            QObject* parent = nullptr)
        : DataChartBox(data_kind, max_points, parent)
        , time_to_(time_to)
        , window_size_(window_size)
        , current_update_parameters_({
        data_kind,
        time_to,
        std::vector<QString>(),
        std::vector<QString>(),
        std::vector<QString>(),
        std::vector<quint64>(),
        std::vector<bool>(),
        std::vector<quint64>()})
    {
    }

    /**
     * @brief Updata the internal series with one point for each series.
     *
     * Get a map of vectors \c new_data .
     * This map has key the unique id for each series to update and as value a vector of points SORTED
     * to add in the specific series.
     */
    void update(
            std::map<quint64, QVector<QPointF>>& new_data,
            quint64 time_to);

    //! Get parameters from an internal chartbox to get next data point
    UpdateParameters get_update_parameters();

    /**
     * @brief Add new series
     *
     * Create a new \c DataModel and a mapper related to it.
     *
     * @return The mapper created (and stored in \c mappers_ )
     */
    QtCharts::QVXYModelMapper* add_series(
            QString statistic_kind,
            bool cumulative,
            quint64 cumulative_interval,
            models::EntityId source_id,
            models::EntityId target_id,
            quint64 max_points);

    //! Eliminate all series
    void clear_charts() override;

    //! Delete the series created in the number \c series_order_index regarding the currently existing ones
    void delete_series_by_order_index(
            quint64 series_order_index) override;


    void recalculate_y_axis() override;

    void set_max_points(
            quint64 series_index,
            quint64 max_points);

protected:

    //! Store last time so next update use it as from time
    quint64 time_to_;

    //! Size of the window that is being shown. This value is used to recalculate the axis.
    quint64 window_size_;

    //! Do not recalculate parameters each time is updated but when series change
    UpdateParameters current_update_parameters_;
};


#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICCHARTBOX_H
