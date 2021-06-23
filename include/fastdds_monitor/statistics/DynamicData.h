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
 * @file DynamicData.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICDATA_H
#define _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICDATA_H

#include <QtCore/QObject>
#include <fastdds_monitor/statistics/DynamicChartBox.h>

/**
 * @brief TODO
 */
class DynamicData : public QObject
{
    Q_OBJECT

public:

    ~DynamicData();

    //! Updata an internal chartbox with one point for each series
    void update(
        quint64 chartbox_id,
        std::vector<QPointF> new_data,
        quint64 time_to);

    //! Get parameters from an internal chartbox to get next data point
    UpdateParameters get_update_parameters(quint64 chartbox_id);

public slots:

    //! Add a new series in an internal chartbox
    QtCharts::QVXYModelMapper* add_series(
        quint64 chartbox_id,
        QString statistic_kind,
        QString source_id,
        QString target_id);

    //! Add a new internal Chartbox
    quint64 add_chartbox(
        QString data_kind,
        quint64 time_to);

    //! Get max Y value in all the internal series
    qreal axis_y_max(
        quint64 chartbox_id);

    //! Get min Y value in all the internal series
    qreal axis_y_min(
        quint64 chartbox_id);

    //! Send clear chart to internal chartbox
    void clear_charts(quint64 chartbox_id);


protected:

    //! Unique id of the new chartbox to add
    static quint64 last_id_;

    //! Internal chartboxes map by id
    std::map<quint64, DynamicChartBox*> chartboxes_;
};

#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICDATA_H
