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
