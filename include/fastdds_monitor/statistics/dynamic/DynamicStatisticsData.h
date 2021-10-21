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
 * @file DynamicStatisticsData.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICDATA_H
#define _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICDATA_H

#include <QtCore/QObject>
#include <fastdds_monitor/statistics/StatisticsData.h>
#include <fastdds_monitor/statistics/dynamic/DynamicDataChartBox.h>

/**
 * @brief Handle all the connections between QML and the dynamic data / real time data
 *
 * It maintains a map with key a unique id given by a static variable, and as value the
 * \c DynamicChartBox related with this id.
 *
 * It gets with slots the QML signals sent from dynamic data related methods.
 * Most of these methods uses the internal id to the chartbox to reference with chartbox must be affected.
 */
class DynamicStatisticsData : public StatisticsData
{
    Q_OBJECT

public:

    // Inherit parent constructors/destructors
    using StatisticsData::StatisticsData;

    //! Updata an internal chartbox with one point for each series
    void update(
            quint64 chartbox_id,
            std::map<quint64, QVector<QPointF>>& new_data,
            quint64 time_to);

    //! Get parameters from an internal chartbox to get next data point
    UpdateParameters get_update_parameters(
            quint64 chartbox_id);

public slots:

    //! Add a new series in an internal chartbox
    QtCharts::QVXYModelMapper* add_series(
            quint64 chartbox_id,
            QString statistic_kind,
            bool cumulative,
            quint64 cumulative_interval,
            QString source_id,
            QString target_id);

    //! Add a new internal Chartbox
    quint64 add_chartbox(
            QString data_kind,
            quint64 time_to,
            quint64 window_size);
};

#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICDATA_H
