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

#include <fastdds_monitor/statistics/DynamicChartBox.h>
#include <fastdds_monitor/model/dynamic/DynamicDataModel.h>

void DynamicChartBox::add_series(
        QString statistic_kind,
        models::EntityId source_id,
        models::EntityId target_id /* = ID_INVALID */)
{
    qDebug() << "Add mapper with statistics: " << statistic_kind
             << " with source: " << source_id
             << " and with target: " << target_id;

    auto new_data_model = new models::DynamicDataModel(statistic_kind, source_id, target_id);

    // Add it to series collection
    series_.push_back(new_data_model);

    auto mapper = new QtCharts::QVXYModelMapper();
    mapper->setModel(new_data_model);
    mapper->setXColumn(0);
    mapper->setYColumn(1);

    // Add it to mappers collection
    mappers_.push_back(mapper);
}

void DynamicChartBox::update(std::vector<QPointF> new_data)
{
    if(new_data.size() != series_.size())
    {
        qWarning() << "Updating model with no data: ";
    }
    else
    {
        qDebug() << "Updating model with id: " << id_;

        for (size_t i = 0; i < series_.size(); i++)
        {
            series_[i]->handleNewPoint(new_data[i]);
        }
    }

    update_frame_();
}

void DynamicChartBox::update_frame_()
{
    last_x_ += refresh_size_;

    // TODO check if axis must be changed here or in QML
}
