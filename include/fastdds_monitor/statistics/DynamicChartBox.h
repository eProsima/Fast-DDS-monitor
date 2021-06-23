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

struct UpdateParameters
{
    QString data_kind;
    quint64 time_from;
    std::vector<QString> source_ids;
    std::vector<QString> target_ids;
    std::vector<QString> statistics_kinds;
};

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
            quint64 time_to,
            QObject* parent = nullptr)
        : QObject(parent)
        , id_(id)
        , data_kind_(data_kind)
        , time_to_(time_to)
        , axisYMax_(10)
        , axisYMin_(0)
    {
    }

    ~DynamicChartBox();

    //! Updata the internal series with one point for each series and set new \c time_to
    void update(std::vector<QPointF> new_data, quint64 time_to);

    //! Get parameters from an internal chartbox to get next data point
    UpdateParameters get_update_parameters();

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

    /**
     * @brief Add new series
     *
     * Create a new \c DynamicDataModel and a mapper related to it
     */
    QtCharts::QVXYModelMapper* add_series(
        QString statistic_kind,
        models::EntityId source_id,
        models::EntityId target_id = models::ID_INVALID);

signals:

    //! Signal to communicate that max Y axis has changed
    void axisYMaxChanged();
    //! Signal to communicate that min Y axis has changed
    void axisYMinChanged();

protected:

    //! Map of ModelMappers reference by unique id from this chartbox
    std::map<quint64, QtCharts::QVXYModelMapper*> mappers_;
    //! Map of \c DynamicDataModel reference by unique id from this chartbox
    std::map<quint64, models::DynamicDataModel*> series_;

    //! Unique id of this chatbox referenced by upper DynamicData
    quint64 id_;

    //! String with data_kind of this chartbox series
    QString data_kind_;

    //! Time to of last point stored
    quint64 time_to_;

    //! Max Y axis size
    qreal axisYMax_;

    //! Min Y axis size
    qreal axisYMin_;

    //! Unique id of the new chartbox to add
    static quint64 last_id_;
};


#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DYNAMIC_DYNAMICCHARTBOX_H