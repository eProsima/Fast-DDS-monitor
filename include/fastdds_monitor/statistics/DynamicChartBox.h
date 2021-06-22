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
 * @file DynamicChartBox.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICCHARTBOX_H
#define _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICCHARTBOX_H

#include <QtCore/QObject>
#include <QtCharts/QVXYModelMapper>

#include <fastdds_monitor/model/dynamic/DynamicDataModel.h>

/**
 * @brief TODO
 */
class DynamicChartBox : public QObject
{
    Q_OBJECT

public:
    DynamicChartBox(
            quint64 id,
            QString data_kind,
            quint64 last_x,
            quint64 frame_size,
            quint64 refresh_size,
            QObject* parent)
        : QObject(parent)
        , id_(id)
        , data_kind_(data_kind)
        , last_x_(last_x)
        , frame_size_(frame_size)
        , refresh_size_(refresh_size)
    {
    }

    void update(std::vector<QPointF> new_data);

    QString data_kind()
    {
        return data_kind_;
    }

    quint64 last_x()
    {
        return last_x_;
    }

    quint64 frame_size()
    {
        return frame_size_;
    }

    quint64 refresh_size()
    {
        return refresh_size_;
    }

public slots:

    void add_series(
        QString statistic_kind,
        models::EntityId source_id,
        models::EntityId target_id = models::ID_INVALID);

protected:

    void update_frame_();

    std::vector<QtCharts::QVXYModelMapper*> mappers_;
    std::vector<models::DynamicDataModel*> series_;

    quint64 id_;
    QString data_kind_;
    quint64 last_x_;
    quint64 frame_size_;
    quint64 refresh_size_;
};


#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICCHARTBOX_H
