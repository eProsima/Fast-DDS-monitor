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
}

const QVector<QPointF>& DataModel::get_data() const
{
    return m_data_;
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
