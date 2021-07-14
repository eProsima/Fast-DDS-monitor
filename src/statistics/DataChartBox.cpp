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
        quint64 real_id_ = series_ids_[series_order_index];

        qDebug() << "Deleting real id " << real_id_;

        // Delete mapper and series
        delete mappers_[real_id_];
        mappers_.erase(real_id_);
        delete series_[real_id_];
        series_.erase(real_id_);
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

    setAxisYMax(Y_MAX_DEFAULT);
    setAxisYMin(Y_MIN_DEFAULT);
    setAxisXMax(X_MAX_DEFAULT);
    setAxisXMin(X_MIN_DEFAULT);
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

            // Do not use else if because first value could be both
            if (point.ry() <= axisYMin_)
            {
                setAxisYMin(point.ry() - 1);
            }

            // X is not updated to speed up the update
            // In historic, x is updated after include the points and in dynamic is updated dynamically
        }
    }
}

qreal DataChartBox::axisYMax() const
{
    if (axisYMax_ == Y_MAX_DEFAULT)
    {
        return 1;
    }
    return axisYMax_;
}

qreal DataChartBox::axisYMin() const
{
    if (axisYMin_ == Y_MIN_DEFAULT)
    {
        return 0;
    }
    return axisYMin_;
}

quint64 DataChartBox::axisXMax() const
{
    if (axisXMax_ == X_MAX_DEFAULT)
    {
        return 1;
    }
    return axisXMax_;
}

quint64 DataChartBox::axisXMin() const
{
    if (axisXMin_ == X_MIN_DEFAULT)
    {
        return 0;
    }
    return axisXMin_;
}

void DataChartBox::setAxisYMax(
        qreal axisYMax)
{
    if (round_axis_)
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
    if (round_axis_)
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

void DataChartBox::newXValue(
        quint64 x)
{
    if (x >= axisXMax_)
    {
        setAxisXMax(x + 1);
    }

    if (x <= axisXMin_)
    {
        setAxisXMin(x - 1);
    }
}

QVector<QPointF> DataChartBox::get_data(
        quint64 series_index)
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

    assert(series_index < series_ids_.size());
    quint64 real_id = series_ids_[series_index];

    auto series_it_ = series_.find(real_id);
    assert(series_it_ != series_.end());

    // These two arguments must be created beforehand as the method requires references
    // Could be const references if QPointF had its getters as const, but it doesnt
    return series_it_->second->get_data();
}

std::vector<QVector<QPointF>> DataChartBox::get_data()
{
    std::vector<QVector<QPointF>> datas(series_.size());

    size_t i = 0;
    // Must be sorted by id, map could not return the correct order
    for (quint64 id : series_ids_)
    {
        auto series_it_ = series_.find(id);
        assert(series_it_ != series_.end());

        datas[i++] = series_it_->second->get_data();
    }

    return datas;
}
