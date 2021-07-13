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
    QtCharts::QVXYModelMapper* add_series(
            quint64 chartbox_id,
            QVector<QPointF> new_series);

public slots:

    //! Add a new internal Chartbox
    quint64 add_chartbox(
            QString data_kind);
};

#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_HISTORIC_HISTORICDATA_H
