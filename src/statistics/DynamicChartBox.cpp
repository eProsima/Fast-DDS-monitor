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

#include <fastdds_monitor/statistics/DynamicChartBox.h>
#include <fastdds_monitor/model/dynamic/DynamicDataModel.h>
#include <fastdds_monitor/utils.h>

quint64 DynamicChartBox::last_id_ = 0;

DynamicChartBox::~DynamicChartBox()
{
    clear_charts();
}

QtCharts::QVXYModelMapper* DynamicChartBox::add_series(
        QString statistic_kind,
        models::EntityId source_id,
        models::EntityId target_id /* = ID_INVALID */)
{
    const std::lock_guard<std::mutex> lock(mutex_);

    qDebug() << "Add mapper with statistics: " << statistic_kind
             << " with source: " << source_id
             << " and with target: " << target_id;

    auto new_data_model = new models::DynamicDataModel();

    // Add it to series collection
    series_.insert({last_id_, new_data_model});

    auto mapper = new QtCharts::QVXYModelMapper();
    mapper->setModel(new_data_model);
    mapper->setXColumn(0);
    mapper->setYColumn(1);

    // Add it to mappers collection
    mappers_.insert({last_id_, mapper});

    current_update_parameters_.series_ids.push_back(last_id_);
    current_update_parameters_.source_ids.push_back(source_id);
    current_update_parameters_.target_ids.push_back(target_id);
    current_update_parameters_.statistics_kinds.push_back(statistic_kind);

    last_id_++;
    return mapper;
}

void DynamicChartBox::delete_series_by_index(
        quint64 series_index)
{
    const std::lock_guard<std::mutex> lock(mutex_);

    qDebug() << "Deleting series " << series_index << " in chartbox with series: " << series_.size();

    if (series_index >= current_update_parameters_.series_ids.size())
    {
        qCritical() << "Error deleting series. Series does not exist in Chartbox. Probably race condition problem!";
    }
    else
    {
        // This is the index that this chartbox internally handles regarding the currently deleting series
        quint64 real_index_ = current_update_parameters_.series_ids[series_index];

        qDebug() << "Deleting real index " << real_index_;

        // Delete mapper and series
        delete mappers_[real_index_];
        mappers_.erase(real_index_);
        delete series_[real_index_];
        series_.erase(real_index_);

        // Delete the data so it is not updated next time calling get_data
        // It is deleting with series_index as are vectors and not maps, so the actual element to erase is in the
        // same position of creation, as in QML
        current_update_parameters_.series_ids.erase(current_update_parameters_.series_ids.begin() + series_index);
        current_update_parameters_.source_ids.erase(current_update_parameters_.source_ids.begin() + series_index);
        current_update_parameters_.target_ids.erase(current_update_parameters_.target_ids.begin() + series_index);
        current_update_parameters_.statistics_kinds.erase(
            current_update_parameters_.statistics_kinds.begin() + series_index);
    }
}

void DynamicChartBox::update(
        std::map<quint64, std::vector<QPointF>>& new_data,
        quint64 time_to)
{
    const std::lock_guard<std::mutex> lock(mutex_);

    // Update internal timer so next call to get data use it as from
    time_to_ = time_to;

    for (auto points : new_data)
    {
        for (auto point : points.second)
        {
            series_[points.first]->handleNewPoint(point);
            if (point.ry() >= axisYMax_)
            {
                setAxisYMax(point.ry() + 1);
            }
            else if (point.ry() <= axisYMin_)
            {
                setAxisYMin(point.ry() - 1);
            }
        }
    }
}

qreal DynamicChartBox::axisYMax()
{
    return axisYMax_;
}

qreal DynamicChartBox::axisYMin()
{
    return axisYMin_;
}

void DynamicChartBox::setAxisYMax(
        qreal axisYMax)
{
    axisYMax_ = axisYMax;
}

void DynamicChartBox::setAxisYMin(
        qreal axisYMin)
{
    axisYMin_ = axisYMin;
}

UpdateParameters DynamicChartBox::get_update_parameters()
{
    const std::lock_guard<std::mutex> lock(mutex_);
    current_update_parameters_.time_from = time_to_;
    return current_update_parameters_;
}

void DynamicChartBox::clear_charts()
{
    const std::lock_guard<std::mutex> lock(mutex_);

    qDebug() << "Clearing chartbox: " << id_;

    for (auto m : mappers_)
    {
        delete m.second;
    }
    mappers_.clear();

    for (auto s : series_)
    {
        delete s.second;
    }
    series_.clear();

    setAxisYMax(std::numeric_limits<qreal>::min());
    setAxisYMin(std::numeric_limits<qreal>::max());

    current_update_parameters_.series_ids.clear();
    current_update_parameters_.source_ids.clear();
    current_update_parameters_.target_ids.clear();
    current_update_parameters_.statistics_kinds.clear();
}
