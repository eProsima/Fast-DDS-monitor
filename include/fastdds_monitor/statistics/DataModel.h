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

/**
 * @file DataModel.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DATAMODEL_H
#define _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DATAMODEL_H

#include <QAbstractTableModel>
#include <QtCore/QObject>
#include <QPointF>

/**
 * @brief Class to handle a vector of points and a QML series, related by a mapper instance
 */
class DataModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    //! Default costructor. Connects \c newPointAdded with this same object \c addNewPoint
    DataModel()
    {
        QObject::connect(this, &DataModel::newPointAdded, this, &DataModel::addNewPoint,
                Qt::QueuedConnection);
    }

    DataModel(
            QVector<QPointF> data)
        : m_data_(data)
    {
        QObject::connect(this, &DataModel::newPointAdded, this, &DataModel::addNewPoint,
                Qt::QueuedConnection);
    }

    //! Number of rows
    int rowCount(
            const QModelIndex& parent = QModelIndex()) const;
    //! Number of columns
    int columnCount(
            const QModelIndex& parent = QModelIndex()) const;
    //! Data header
    QVariant headerData(
            int section,
            Qt::Orientation orientation,
            int role = Qt::DisplayRole) const;
    //! Point data getter
    QVariant data(
            const QModelIndex& index,
            int role = Qt::DisplayRole) const;

    //! Function to add a new point by sending signal \c newPointAdded
    void handleNewPoint(
            const QPointF& point);

    const QVector<QPointF>& get_data() const;

    std::pair<qreal, qreal> limit_y_value(
            const quint64 from = 0,
            const quint64 to = std::numeric_limits<quint64>::max()) const;

signals:

    //! Signal to notify a new point must be added
    void newPointAdded(
            const QPointF& point);

protected:

    //! Function to add a new point to the model
    void addNewPoint(
            const QPointF& point);

    //! Vector of points (not sorted)
    QVector<QPointF> m_data_;
};

#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DATAMODEL_H
