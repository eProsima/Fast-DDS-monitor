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

#define Y_MAX_DEFAULT std::numeric_limits<qreal>::lowest()
#define Y_MIN_DEFAULT std::numeric_limits<qreal>::max()
#define X_MAX_DEFAULT std::numeric_limits<quint64>::min()
#define X_MIN_DEFAULT std::numeric_limits<quint64>::max()

/**
 * @brief Class that represets a chartbox in main panel
 */
class DataChartBox : public QObject
{
    Q_OBJECT

public:

    DataChartBox(
            QString data_kind,
            quint64 max_points = 0,
            QObject* parent = nullptr)
        : QObject(parent)
        , data_kind_(data_kind)
        , axisYMax_(Y_MAX_DEFAULT)
        , axisYMin_(Y_MIN_DEFAULT)
        , axisXMax_(X_MAX_DEFAULT)
        , axisXMin_(X_MIN_DEFAULT)
        , round_axis_(false)
        , max_points_(max_points)
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
    //! Set the new Y as max/min if it is bigger/lower than the current one
    void newYValue(
            qreal y);
    //! Set the new X max axis size
    void setAxisXMax(
            quint64 axisXMax);
    //! Set the new X min axis size
    void setAxisXMin(
            quint64 axisXMin);
    //! Set the new X as max/min if it is bigger/lower than the current one
    void newXValue(
            quint64 x);

    const QVector<QPointF>& get_data(
            quint64 series_index);

    virtual void recalculate_y_axis();

    void reset_axis(
            bool x_axis = true,
            bool y_axis = true);

    //! Set the max number of data points allowed in a specific DataModel
    void set_max_points(
            quint64 series_order_index,
            quint64 max_points);

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

    quint64 max_points_;
};

#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_DATACHARTBOX_H
