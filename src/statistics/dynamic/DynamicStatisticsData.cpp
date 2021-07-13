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

#include <QDebug>

#include <fastdds_monitor/statistics/dynamic/DynamicStatisticsData.h>
#include <fastdds_monitor/statistics/dynamic/DynamicDataChartBox.h>

void DynamicStatisticsData::update(
        quint64 chartbox_id,
        std::map<quint64, QVector<QPointF>>& new_data,
        quint64 time_to)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    DynamicDataChartBox* d_chartbox = dynamic_cast<DynamicDataChartBox*>(it->second);

    d_chartbox->update(new_data, time_to);
}

QtCharts::QVXYModelMapper* DynamicStatisticsData::add_series(
        quint64 chartbox_id,
        QString statistic_kind,
        QString source_id,
        QString target_id)
{
    qDebug() << "Adding dynamic serie to chartbox id: " << chartbox_id;

    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    DynamicDataChartBox* d_chartbox = dynamic_cast<DynamicDataChartBox*>(it->second);

    return d_chartbox->add_series(statistic_kind, source_id, target_id);
}

quint64 DynamicStatisticsData::add_chartbox(
        QString data_kind,
        quint64 time_to)
{
    return StatisticsData::add_chartbox(new DynamicDataChartBox(data_kind, time_to));
}

UpdateParameters DynamicStatisticsData::get_update_parameters(
        quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    DynamicDataChartBox* d_chartbox = dynamic_cast<DynamicDataChartBox*>(it->second);

    return d_chartbox->get_update_parameters();
}
