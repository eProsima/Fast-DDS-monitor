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
 * @file DynamicDataModel.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_DYNAMIC_DYNAMICDATAMODEL_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_DYNAMIC_DYNAMICDATAMODEL_H

#include <QAbstractTableModel>
#include <QtCore/QObject>
#include <QPointF>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/model/model_types.h>

namespace models {

/**
 * @brief Class to handle a vector of points and a QML series, related by a mapper instance
 */
class DynamicDataModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    //! Default costructor. Connects \c newPointAdded with this same object \c addNewPoint
    DynamicDataModel()
    {
        QObject::connect(this, &DynamicDataModel::newPointAdded, this, &DynamicDataModel::addNewPoint,
                Qt::QueuedConnection);
    }

    //! Function to add a new point by sending signal \c newPointAdded
    void handleNewPoint(
            const QPointF& point);

signals:

    //! Signal to notify a new point must be added
    void newPointAdded(
            const QPointF& point);

public:

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

protected:

    //! Function to add a new point to the model
    void addNewPoint(
            const QPointF& point);

    //! Vector of points (not sorted)
    std::vector<QPointF> m_data;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_DYNAMIC_DYNAMICDATAMODEL_H
