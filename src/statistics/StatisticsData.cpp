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

#include <QDateTime>
#include <QDebug>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QXYSeries>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickView>

#include <limits>

#include <fastdds_monitor/statistics/StatisticsData.h>
#include <fastdds_monitor/utils.h>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(
        QAbstractSeries*)

Q_DECLARE_METATYPE(
    QAbstractAxis*)

std::atomic<quint64> StatisticsData::last_id_(0);

StatisticsData::StatisticsData(
        QObject* parent)
    : QObject(parent)
{
}

StatisticsData::~StatisticsData()
{
    for (auto c : chartboxes_)
    {
        delete c.second;
    }
}

void StatisticsData::delete_series(
        quint64 chartbox_id,
        quint64 series_index)
{
    qDebug() << "Deleting series " << series_index << " to chartbox id: " << chartbox_id;

    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    it->second->delete_series_by_order_index(series_index);
}

quint64 StatisticsData::add_chartbox(
        DataChartBox* chartbox)
{
    qDebug() << "Adding chartbox with id: " << last_id_;

    quint64 new_id = last_id_++;

    chartboxes_.insert({new_id, chartbox});
    return new_id;
}

void StatisticsData::delete_chartbox(
        quint64 chartbox_id)
{
    qDebug() << "Erasing chartbox with id: " << chartbox_id;

    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    delete it->second;

    chartboxes_.erase(chartbox_id);
}

void StatisticsData::clear_charts(
        quint64 chartbox_id)
{
    qDebug() << "Clearing charts from: " << chartbox_id;

    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    it->second->clear_charts();
}

qreal StatisticsData::axisYMax(
        quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->axisYMax();
}

qreal StatisticsData::axisYMin(
        quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->axisYMin();
}

quint64 StatisticsData::axisXMax(
        quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->axisXMax();
}

quint64 StatisticsData::axisXMin(
        quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->axisXMin();
}

void StatisticsData::setAxisYMax(
        quint64 chartbox_id,
        qreal axisYMax)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->setAxisYMax(axisYMax);
}

void StatisticsData::setAxisYMin(
        quint64 chartbox_id,
        qreal axisYMin)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->setAxisYMin(axisYMin);
}

void StatisticsData::setAxisXMax(
        quint64 chartbox_id,
        quint64 axisXMax)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->setAxisXMax(axisXMax);
}

void StatisticsData::setAxisXMin(
        quint64 chartbox_id,
        quint64 axisXMin)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->setAxisXMin(axisXMin);
}

void StatisticsData::newXValue(
        quint64 chartbox_id,
        quint64 x)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    it->second->newXValue(x);
}

bool StatisticsData::contains_chartbox(
        quint64 chartbox_id)
{
    return chartboxes_.count(chartbox_id); // 1 if found, 0 if not
}

const QVector<QPointF>& StatisticsData::get_data(
        quint64 chartbox_id,
        quint64 series_index)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->get_data(series_index);
}

void StatisticsData::recalculate_y_axis(
        quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    it->second->recalculate_y_axis();
}

qreal StatisticsData::get_max_real()
{
    return std::numeric_limits<qreal>::max();
}

qreal StatisticsData::get_min_real()
{
    return std::numeric_limits<qreal>::lowest();
}

quint64 StatisticsData::get_max_uint()
{
    return std::numeric_limits<quint64>::max();
}

quint64 StatisticsData::get_min_uint()
{
    return std::numeric_limits<quint64>::min();
}
