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

#include <iostream>
#include <math.h>
#include <mutex>

#include <QDebug>

#include <fastdds_monitor/statistics/DataChartBox.h>
#include <fastdds_monitor/statistics/DataModel.h>

std::atomic<quint64> DataChartBox::last_id_(0);

DataChartBox::~DataChartBox()
{
    clear_charts();
}

QtCharts::QVXYModelMapper* DataChartBox::add_series(
    DataModel* data_model,
    quint64& new_series_index)
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

    new_series_index = last_id_++;

    qDebug() << "Adding series with id: " << new_series_index;

    // Add it to series collection
    series_.insert({new_series_index, data_model});

    auto mapper = new QtCharts::QVXYModelMapper();
    mapper->setModel(data_model);
    mapper->setXColumn(0);
    mapper->setYColumn(1);

    // Add it to mappers collection
    mappers_.insert({new_series_index, mapper});
    series_ids_.push_back(new_series_index);

    return mapper;
}

QtCharts::QVXYModelMapper* DataChartBox::add_series(
    DataModel* data_model)
{
    quint64 _foo;
    return add_series(data_model, _foo);
}

void DataChartBox::delete_series_by_order_index(
        quint64 series_order_index)
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

    qDebug() << "Deleting series " << series_order_index << " in chartbox with series: " << series_.size();

    if (series_order_index >= series_ids_.size())
    {
        qCritical() << "Error deleting series. Series does not exist in Chartbox. Probably race condition problem!";
    }
    else
    {
        // This is the index that this chartbox internally handles regarding the currently deleting series
        quint64 real_index_ = series_ids_[series_order_index];

        qDebug() << "Deleting real index " << real_index_;

        // Delete mapper and series
        delete mappers_[real_index_];
        mappers_.erase(real_index_);
        delete series_[real_index_];
        series_.erase(real_index_);
        series_ids_.erase(series_ids_.begin() + series_order_index);
    }
}

void DataChartBox::clear_charts()
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

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

    series_ids_.clear();

    setAxisYMax(std::numeric_limits<qreal>::min());
    setAxisYMin(std::numeric_limits<qreal>::max());
    setAxisXMax(std::numeric_limits<quint64>::min());
    setAxisXMin(std::numeric_limits<quint64>::max());
}

void DataChartBox::update(
        std::map<quint64, QVector<QPointF>> new_data)
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

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

            if (point.rx() >= axisXMax_)
            {
                setAxisXMax(point.rx());
            }
            else if (point.rx() <= axisXMin_)
            {
                setAxisXMin(point.rx());
            }
        }
    }
}

qreal DataChartBox::axisYMax() const
{
    return axisYMax_;
}

qreal DataChartBox::axisYMin() const
{
    return axisYMin_;
}

quint64 DataChartBox::axisXMax() const
{
    return axisXMax_;
}

quint64 DataChartBox::axisXMin() const
{
    return axisXMin_;
}

void DataChartBox::setAxisYMax(
        qreal axisYMax)
{
    if(round_axis_)
    {
        axisYMax_ = std::round(axisYMax);
    }
    else
    {
        axisYMax_ = axisYMax;
    }
}

void DataChartBox::setAxisYMin(
        qreal axisYMin)
{
    if(round_axis_)
    {
        axisYMin_ = std::round(axisYMin);
    }
    else
    {
        axisYMin_ = axisYMin;
    }
}

void DataChartBox::setAxisXMax(
        quint64 axisXMax)
{
    axisXMax_ = axisXMax;
}

void DataChartBox::setAxisXMin(
        quint64 axisXMin)
{
    axisXMin_ = axisXMin;
}
