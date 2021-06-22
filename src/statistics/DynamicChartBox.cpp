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
#include <fastdds_monitor/utils.h>

DynamicChartBox::~DynamicChartBox()
{
    for(auto m : mappers_)
    {
        delete m;
    }

    for (auto s : series_)
    {
        delete s;
    }
}

QtCharts::QVXYModelMapper* DynamicChartBox::add_series(
        QString statistic_kind,
        models::EntityId source_id,
        models::EntityId target_id /* = ID_INVALID */)
{
    qDebug() << "Add mapper with statistics: " << statistic_kind
             << " with source: " << source_id
             << " and with target: " << target_id;

    qDebug() << "Actual time to set points now: " << utils::to_QString(utils::now());
    qDebug() << "Actual time to set points: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    qDebug() << "Actual time to set points: " << (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - 10000);

    auto new_data_model = new models::DynamicDataModel(statistic_kind, source_id, target_id);

    new_data_model->handleNewPoint(
        QPointF(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(), 1));

    new_data_model->handleNewPoint(
        QPointF(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - 30000, 1));

    new_data_model->handleNewPoint(
        QPointF(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - 10000, 1));

    // Add it to series collection
    series_.push_back(new_data_model);

    auto mapper = new QtCharts::QVXYModelMapper();
    mapper->setModel(new_data_model);
    mapper->setXColumn(0);
    mapper->setYColumn(1);

    // Add it to mappers collection
    mappers_.push_back(mapper);


    new_data_model->handleNewPoint(
        QPointF(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(), 2));

    new_data_model->handleNewPoint(
        QPointF(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - 30000, 2));

    new_data_model->handleNewPoint(
        QPointF(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - 10000, 2));


    return mapper;
}

void DynamicChartBox::update(std::vector<QPointF> new_data, quint64 time_to)
{
    // Update internal timer so next call to get data use it as from
    time_to_ = time_to;

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
            if(new_data[i].ry() > axisYMax_)
            {
                setAxisYMax(new_data[i].ry());
            }
            else if (new_data[i].ry() < axisYMin_)
            {
                setAxisYMin(new_data[i].ry());
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
    UpdateParameters parameters;
    parameters.data_kind = data_kind_;
    parameters.time_from = time_to_;

    // TODO : store these vectors so it is not needed to create it every time
    for (auto model : series_)
    {
        parameters.source_ids.push_back(model->source_id());
        parameters.target_ids.push_back(model->target_id());
        parameters.statistics_kinds.push_back(model->statistic_kind());
    }

    return parameters;
}
