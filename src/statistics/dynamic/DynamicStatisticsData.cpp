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
        bool cumulative,
        QString source_id,
        QString target_id)
{
    qDebug() << "Adding dynamic serie to chartbox id: " << chartbox_id;

    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    DynamicDataChartBox* d_chartbox = dynamic_cast<DynamicDataChartBox*>(it->second);

    return d_chartbox->add_series(statistic_kind, cumulative, source_id, target_id);
}

quint64 DynamicStatisticsData::add_chartbox(
        QString data_kind,
        quint64 time_to,
        quint64 window_size)
{
    return StatisticsData::add_chartbox(new DynamicDataChartBox(data_kind, time_to, window_size));
}

UpdateParameters DynamicStatisticsData::get_update_parameters(
        quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    DynamicDataChartBox* d_chartbox = dynamic_cast<DynamicDataChartBox*>(it->second);

    return d_chartbox->get_update_parameters();
}
