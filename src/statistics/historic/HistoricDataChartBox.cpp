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
