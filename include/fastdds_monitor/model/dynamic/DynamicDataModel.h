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
 * @brief TODO
 */
class DynamicDataModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    DynamicDataModel(
            QString statistic_kind,
            models::EntityId source_id,
            models::EntityId target_id = ID_INVALID)
        : source_id_(source_id)
        , target_id_(target_id)
        , statistic_kind_(statistic_kind)
    {
        QObject::connect(this, &DynamicDataModel::newPointAdded, this, &DynamicDataModel::addNewPoint,
                Qt::QueuedConnection);
    }

    void handleNewPoint(const QPointF& point);

signals:
    void newPointAdded(const QPointF& point);

public:
    DynamicDataModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    models::EntityId source_id()
    {
        return source_id_;
    }

    models::EntityId target_id()
    {
        return target_id_;
    }

    QString statistic_kind()
    {
        return statistic_kind_;
    }

protected:
    void addNewPoint(const QPointF& point);

    std::vector<QPointF> m_data;
    models::EntityId source_id_;
    models::EntityId target_id_;
    QString statistic_kind_;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_DYNAMIC_DYNAMICDATAMODEL_H
