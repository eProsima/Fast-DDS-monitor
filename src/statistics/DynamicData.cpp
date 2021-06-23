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

#include <fastdds_monitor/statistics/DynamicData.h>
#include <fastdds_monitor/statistics/DynamicChartBox.h>

quint64 DynamicData::last_id_ = 0;

DynamicData::~DynamicData()
{
    for (auto c : chartboxes_)
    {
        delete c.second;
    }
}

void DynamicData::update(
    quint64 chartbox_id,
    std::vector<QPointF> new_data,
    quint64 time_to)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    it->second->update(new_data, time_to);
}

QtCharts::QVXYModelMapper* DynamicData::add_series(
    quint64 chartbox_id,
    QString statistic_kind,
    QString source_id,
    QString target_id)
{
    qDebug() << "Addin serie to chartbox id: " << chartbox_id;

    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->add_series(statistic_kind, source_id, target_id);
}

quint64 DynamicData::add_chartbox(
    QString data_kind,
    quint64 time_to)
{
    qDebug() << "Addin chartbox with id: " << last_id_;

    chartboxes_.insert({last_id_, new DynamicChartBox(last_id_, data_kind, time_to)});
    return last_id_++;
}

UpdateParameters DynamicData::get_update_parameters(quint64 chartbox_id)
{
    qDebug() << "Getting parameters from: " << chartbox_id;

    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->get_update_parameters();
}

qreal DynamicData::axis_y_max(
    quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->axisYMax();
}

qreal DynamicData::axis_y_min(
    quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->axisYMin();
}
