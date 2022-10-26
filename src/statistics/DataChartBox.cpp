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

#include <cmath>
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

    reset_axis();
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
            newYValue(point.ry());
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

void DataChartBox::newYValue(
        qreal y)
{
    if (y != 0)
    {
        if (y > axisYMax_)
        {
            setAxisYMax(y);
        }

        if (y < axisYMin_)
        {
            setAxisYMin(y);
        }

        // if (axisYMin_ == 0 && axisYMax_ != y)
        // {
        //     std::cout << "entra en 0" << std::endl;
        //     setAxisYMin(y);
        // }

        // // Have to be differents to plot values
        // if (axisYMax_ == axisYMin_)
        // {
        //     setAxisYMin(0);
        // }
    }
}

void DataChartBox::newXValue(
        quint64 x)
{
    if (x > axisXMax_)
    {
        setAxisXMax(x);
    }

    if (x < axisXMin_)
    {
        setAxisXMin(x);
    }
}

const QVector<QPointF>& DataChartBox::get_data(
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

void DataChartBox::reset_axis(
        bool x_axis,
        bool y_axis)
{
    if (x_axis)
    {
        setAxisXMax(X_MAX_DEFAULT);
        setAxisXMin(X_MIN_DEFAULT);
    }

    if (y_axis)
    {
        setAxisYMax(Y_MAX_DEFAULT);
        setAxisYMin(Y_MIN_DEFAULT);
    }
}

void DataChartBox::recalculate_y_axis()
{
    // Reset axis to default
    reset_axis(false, true);

    // For each series set max and min values as set values
    for (std::pair<quint64, DataModel*> series : series_)
    {
        // Check only the models with values
        if (series.second->get_size())
        {
            std::pair<qreal, qreal> limits = series.second->limit_y_value();
            newYValue(limits.first);
            newYValue(limits.second);
        }
    }
}
