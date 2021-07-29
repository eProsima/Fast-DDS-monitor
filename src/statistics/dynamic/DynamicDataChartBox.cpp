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
#include <iostream>
#include <mutex>

#include <fastdds_monitor/statistics/dynamic/DynamicDataChartBox.h>
#include <fastdds_monitor/utils.h>

QtCharts::QVXYModelMapper* DynamicDataChartBox::add_series(
        QString statistic_kind,
        models::EntityId source_id,
        models::EntityId target_id /* = ID_INVALID */)
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

    quint64 new_id;

    auto new_mapper = DataChartBox::add_series(new DataModel(), new_id);

    if (new_mapper)
    {
        current_update_parameters_.series_ids.push_back(new_id);
        current_update_parameters_.source_ids.push_back(source_id);
        current_update_parameters_.target_ids.push_back(target_id);
        current_update_parameters_.statistics_kinds.push_back(statistic_kind);
    }

    return new_mapper;
}

void DynamicDataChartBox::delete_series_by_order_index(
        quint64 series_order_index)
{
    DataChartBox::delete_series_by_order_index(series_order_index);

    current_update_parameters_.series_ids.erase(
        current_update_parameters_.series_ids.begin() + series_order_index);
    current_update_parameters_.source_ids.erase(
        current_update_parameters_.source_ids.begin() + series_order_index);
    current_update_parameters_.target_ids.erase(
        current_update_parameters_.target_ids.begin() + series_order_index);
    current_update_parameters_.statistics_kinds.erase(
        current_update_parameters_.statistics_kinds.begin() + series_order_index);
}

void DynamicDataChartBox::update(
        std::map<quint64, QVector<QPointF>>& new_data,
        quint64 time_to)
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

    // Update internal timer so next call to get data use it as from
    time_to_ = time_to;

    DataChartBox::update(new_data);
}

UpdateParameters DynamicDataChartBox::get_update_parameters()
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);
    current_update_parameters_.time_from = time_to_;
    return current_update_parameters_;
}

void DynamicDataChartBox::clear_charts()
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

    DataChartBox::clear_charts();

    current_update_parameters_.series_ids.clear();
    current_update_parameters_.source_ids.clear();
    current_update_parameters_.target_ids.clear();
    current_update_parameters_.statistics_kinds.clear();
}

void DynamicDataChartBox::recalculate_y_axis()
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

    // Reset axis to default
    reset_axis(false, true);

    // Get from and to values to set the data that is being shown in that moment
    quint64 time_from = time_to_ - window_size_;

    // For each series set max and min values as set values
    for (std::pair<quint64, DataModel*> series : series_)
    {
        // Note: time_to_ could be used to calculate it, as it would be the same as max time
        std::pair<qreal, qreal> limits = series.second->limit_y_value(time_from);
        newYValue(limits.first);
        newYValue(limits.second);
    }
}