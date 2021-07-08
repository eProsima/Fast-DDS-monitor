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
 * @file DataChartBox.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DATACHARTBOX_H
#define _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DATACHARTBOX_H

#include <atomic>
#include <limits>
#include <mutex>

#include <QtCore/QObject>
#include <QtCharts/QVXYModelMapper>

#include <fastdds_monitor/statistics/DataModel.h>

/**
 * @brief Class that represets a chartbox in main panel
 */
class DataChartBox : public QObject
{
    Q_OBJECT
    // TODO
    // Q_PROPERTY(qreal axisYMax READ axisYMax NOTIFY axisYMaxChanged)
    // Q_PROPERTY(qreal axisYMin READ axisYMin NOTIFY axisYMinChanged)
    // Q_PROPERTY(qreal axisXMax READ axisXMax NOTIFY axisXMaxChanged)
    // Q_PROPERTY(qreal axisXMin READ axisXMin NOTIFY axisXMinChanged)

public:

    DataChartBox(
            QString data_kind,
            QObject* parent = nullptr)
        : QObject(parent)
        , data_kind_(data_kind)
        , axisYMax_(std::numeric_limits<qreal>::min())
        , axisYMin_(std::numeric_limits<qreal>::max())
        , axisXMax_(std::numeric_limits<quint64>::min())
        , axisXMin_(std::numeric_limits<quint64>::max())
        , round_axis_(true)
    {
    }

    ~DataChartBox();

    /**
     * @brief Updata the internal series with one point for each series.
     *
     * Get a map of vectors \c new_data .
     * This map has key the unique id for each series to update and as value a vector of points SORTED
     * to add in the specific series.
     */
    void update(
            std::map<quint64, QVector<QPointF>> new_data);

    //! Delete the series created in the number \c series_order_index regarding the currently existing ones
    virtual void delete_series_by_order_index(
            quint64 series_order_index);

    //! Eliminate all series
    virtual void clear_charts();

    //! Get Y max axis size
    qreal axisYMax() const;
    //! Get Y min axis size
    qreal axisYMin() const;
    //! Get X max axis size
    quint64 axisXMax() const;
    //! Get X min axis size
    quint64 axisXMin() const;

    //! Set the new Y max axis size
    void setAxisYMax(
            qreal axisYMax);
    //! Set the new Y min axis size
    void setAxisYMin(
            qreal axisYMin);
    //! Set the new X max axis size
    void setAxisXMax(
            quint64 axisXMax);
    //! Set the new X min axis size
    void setAxisXMin(
            quint64 axisXMin);

// TODO
// signals:

//     //! Signal to communicate that max Y axis has changed
//     void axisYMaxChanged();
//     //! Signal to communicate that min Y axis has changed
//     void axisYMinChanged();
//     //! Signal to communicate that max X axis has changed
//     void axisXMaxChanged();
//     //! Signal to communicate that min X axis has changed
//     void axisXMinChanged();

protected:

    /**
     * @brief Add new series and store in \c new_series_index the id of the new series
     */
    QtCharts::QVXYModelMapper* add_series(
            DataModel* data_model,
            quint64& new_series_index);

    /**
     * @brief Add new series
     */
    QtCharts::QVXYModelMapper* add_series(
            DataModel* data_model);

    //! Map of ModelMappers reference by unique id from this chartbox
    std::map<quint64, QtCharts::QVXYModelMapper*> mappers_;
    //! Map of \c DataModel reference by unique id from this chartbox
    std::map<quint64, DataModel*> series_;

    //! Vector of the ids of the series in this chartbox sorted by creation
    std::vector<quint64> series_ids_;

    //! String with data_kind of this chartbox series
    QString data_kind_;

    //! Max Y axis size
    qreal axisYMax_;
    //! Min Y axis size
    qreal axisYMin_;
    //! Max X axis size
    quint64 axisXMax_;
    //! Min X axis size
    quint64 axisXMin_;

    //! Automatiacally calculate a round axis
    bool round_axis_;

    //! Lock internal series access while creating, deleting or updating
    mutable std::recursive_mutex mutex_;

    //! Unique id of the new chartbox to add
    static std::atomic<quint64> last_id_;
};

#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DATACHARTBOX_H
