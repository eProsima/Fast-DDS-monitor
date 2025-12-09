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
 * @file HistoricStatisticsData.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_STATISTICS_HISTORIC_HISTORICDATA_H
#define _EPROSIMA_FASTDDS_MONITOR_STATISTICS_HISTORIC_HISTORICDATA_H

#include <QtCore/QObject>
#include <fastdds_monitor/statistics/StatisticsData.h>
#include <fastdds_monitor/statistics/historic/HistoricDataChartBox.h>

/**
 * @brief Handle all the connections between QML and the dynamic data / real time data
 *
 * It maintains a map with key a unique id given by a static variable, and as value the
 * \c DynamicChartBox related with this id.
 *
 * It gets with slots the QML signals sent from dynamic data related methods.
 * Most of these methods uses the internal id to the chartbox to reference with chartbox must be affected.
 */
class HistoricStatisticsData : public StatisticsData
{
    Q_OBJECT

public:

    // Inherit parent constructors/destructors
    using StatisticsData::StatisticsData;

    //! Add a new series in an internal chartbox
    QVXYModelMapper* add_series(
            quint64 chartbox_id,
            QVector<QPointF> new_series);

public slots:

    //! Add a new internal Chartbox
    quint64 add_chartbox(
            QString data_kind);
};

#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_HISTORIC_HISTORICDATA_H
