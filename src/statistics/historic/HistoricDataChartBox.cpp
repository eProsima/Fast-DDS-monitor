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

#include <fastdds_monitor/statistics/historic/HistoricDataChartBox.h>

QtCharts::QVXYModelMapper* HistoricDataChartBox::add_series(
        QVector<QPointF> new_series)
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

    quint64 new_id;
    auto mapper = DataChartBox::add_series(new DataModel(), new_id);

    // In case the creation has been successful, add all the data
    if (mapper)
    {
        std::map<quint64, QVector<QPointF>> update_map;
        update_map[new_id] = new_series;
        update(update_map);
    }

    return mapper;
}
