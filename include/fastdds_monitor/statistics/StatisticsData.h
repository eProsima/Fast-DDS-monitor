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
 * @file StatisticsData.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_STATISTICS_STATISTICSDATA_H
#define _EPROSIMA_FASTDDS_MONITOR_STATISTICS_STATISTICSDATA_H

#include <atomic>

#include <QtCore/QObject>
#include <fastdds_monitor/statistics/DataChartBox.h>

/**
 * @brief Handle all the connections between QML and the  data / real time data
 *
 * It maintains a map with key a unique id given by a static variable, and as value the
 * \c ChartBox related with this id.
 *
 * It gets with slots the QML signals sent from  data related methods.
 * Most of these methods uses the internal id to the chartbox to reference with chartbox must be affected.
 */
class StatisticsData : public QObject
{
    Q_OBJECT

public:

    StatisticsData(
            QObject* parent = nullptr);

    ~StatisticsData();

public slots:

    /**
     * Delete a series belongs to an internal Chartbox
     *
     * @warning This method is called with the QML series_index, that is not static for a series, but it is
     * an index in an array that varies. In the unlikely case of deleting two series in less time than C++
     * handles one destruction, it could lead to error
     */
    void delete_series(
            quint64 chartbox_id,
            quint64 series_index);

    //! Delete an internal Chartbox
    void delete_chartbox(
            quint64 chartbox_id);

    //! Send clear chart to internal chartbox
    void clear_charts(
            quint64 chartbox_id);

    //! Get Y max axis size
    qreal axisYMax(
            quint64 chartbox_id);
    //! Get Y min axis size
    qreal axisYMin(
            quint64 chartbox_id);
    //! Get X max axis size
    quint64 axisXMax(
            quint64 chartbox_id);
    //! Get X min axis size
    quint64 axisXMin(
            quint64 chartbox_id);

    //! Set the new Y max axis size
    void setAxisYMax(
            quint64 chartbox_id,
            qreal axisYMax);
    //! Set the new Y min axis size
    void setAxisYMin(
            quint64 chartbox_id,
            qreal axisYMin);
    //! Set the new X max axis size
    void setAxisXMax(
            quint64 chartbox_id,
            quint64 axisXMax);
    //! Set the new X min axis size
    void setAxisXMin(
            quint64 chartbox_id,
            quint64 axisXMin);
    //! Set the new X as max/min if it is bigger/lower than the current one
    void newXValue(
            quint64 chartbox_id,
            quint64 x);

    void save_series_csv(
            quint64 chartbox_id,
            quint64 series_index,
            QString file_name,
            QString data_kind,
            QString chartbox_title,
            QString data_unit,
            QString label);

    void save_chartbox_csv(
            quint64 chartbox_id,
            QString file_name,
            QString data_kind,
            QString chartbox_name,
            QString data_unit,
            QVector<QString> label_names);

    void save_all_csv(
            QString file_name,
            QVector<quint64> chartbox_order,
            QVector<QString> data_kinds,
            QVector<QString> chartbox_name,
            QVector<QString> data_unit,
            QVector<QString> label_names);

protected:

    static void save_csv(
            const QString& file_name,
            const std::vector<QVector<QPointF>>& datas,
            const QVector<QString>& data_kinds,
            const QVector<QString>& chartbox_names,
            const QVector<QString>& data_units,
            const QVector<QString>& label_names,
            const std::string separator = ";");

    static std::map<quint64, std::vector<qreal>> merge_datas(
            const std::vector<QVector<QPointF>>& datas);

    /**
     * Add a new internal Chartbox
     */
    quint64 add_chartbox(
            DataChartBox* chartbox);

    //! Unique id of the new chartbox to add
    static std::atomic<quint64> last_id_;

    //! Internal chartboxes map by id
    std::map<quint64, DataChartBox*> chartboxes_;
};

#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_STATISTICSDATA_H
