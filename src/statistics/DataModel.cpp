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

#include <iostream>
#include <QDebug>

#include <fastdds_monitor/statistics/DataModel.h>

int DataModel::rowCount(
        const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_data_.size());
}

int DataModel::columnCount(
        const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 2;
}

QVariant DataModel::headerData(
        int section,
        Qt::Orientation orientation,
        int role) const
{
    Q_UNUSED(orientation)
    Q_UNUSED(role)

    if (section == 0)
    {
        return "x";
    }
    else
    {
        return "y";
    }
}

QVariant DataModel::data(
        const QModelIndex& index,
        int role) const
{
    Q_UNUSED(role)

    if (index.column() == 0)
    {
        return m_data_[index.row()].x();
    }
    else
    {
        return m_data_[index.row()].y();
    }
}

void DataModel::handleNewPoint(
        const QPointF& point)
{
    emit newPointAdded(point);
}

void DataModel::addNewPoint(
        const QPointF& point)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data_.push_back(point);
    endInsertRows();

    // Remove last point in case it is required
    if (0u != max_points_)
    {
        while(get_size() > max_points_)
        {
            beginRemoveRows(QModelIndex(), 0, 0);
            m_data_.pop_front();
            endRemoveRows();
        }
    }
}

const QVector<QPointF>& DataModel::get_data() const
{
    return m_data_;
}

size_t DataModel::get_size() const
{
    return m_data_.size();
}

std::pair<qreal, qreal> DataModel::limit_y_value(
        const quint64 from /* = 0 */,
        const quint64 to /* = std::numeric_limits<quint64>::max() */) const
{
    qreal max_val = std::numeric_limits<qreal>::lowest();
    qreal min_val = std::numeric_limits<qreal>::max();

    // TODO This may be accelerate with binary search at first
    for (QPointF point : m_data_)
    {
        if (point.rx() >= from && point.rx() < to)
        {
            if (point.ry() > max_val)
            {
                max_val = point.ry();
            }

            if (point.ry() < min_val)
            {
                min_val = point.ry();
            }
        }
    }

    return std::make_pair(min_val, max_val);
}

void DataModel::set_max_points(
        quint64 max_points)
{
    max_points_ = max_points;
}
