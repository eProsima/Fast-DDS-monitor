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
    Q_PROPERTY(qreal axisYMax READ axisYMax NOTIFY axisYMaxChanged)
    Q_PROPERTY(qreal axisYMin READ axisYMin NOTIFY axisYMinChanged)

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
        , axisYMax_(10)
        , axisYMin_(0)
    {
    }

    void update(std::vector<QPointF> new_data);

    QString data_kind() const
    {
        return data_kind_;
    }

    quint64 last_x() const
    {
        return last_x_;
    }

    quint64 frame_size() const
    {
        return frame_size_;
    }

    quint64 refresh_size() const
    {
        return refresh_size_;
    }

    //! Get Y max axis size
    qreal axisYMax();
    //! Get Y min axis size
    qreal axisYMin();

    //! Set the new Y max axis size
    void setAxisYMax(
            qreal axisYMax);
    //! Set the new Y min axis size
    void setAxisYMin(
            qreal axisYMin);

public slots:

    void add_series(
        QString statistic_kind,
        models::EntityId source_id,
        models::EntityId target_id = models::ID_INVALID);

signals:

    //! Signal to communicate that max Y axis has changed
    void axisYMaxChanged();
    //! Signal to communicate that min Y axis has changed
    void axisYMinChanged();

protected:

    void update_frame_();

    std::vector<QtCharts::QVXYModelMapper*> mappers_;
    std::vector<models::DynamicDataModel*> series_;

    quint64 id_;
    QString data_kind_;
    quint64 last_x_;
    quint64 frame_size_;
    quint64 refresh_size_;

    //! Max Y axis size
    qreal axisYMax_;

    //! Min Y axis size
    qreal axisYMin_;
};


#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICCHARTBOX_H
