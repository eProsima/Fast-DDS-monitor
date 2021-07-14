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

#include <fstream>

#include <QDateTime>
#include <QDebug>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QXYSeries>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickView>

#include <fastdds_monitor/statistics/StatisticsData.h>
#include <fastdds_monitor/utils.h>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(
        QAbstractSeries*)

Q_DECLARE_METATYPE(
    QAbstractAxis*)

std::atomic<quint64> StatisticsData::last_id_(0);

StatisticsData::StatisticsData(
        QObject* parent)
    : QObject(parent)
{
}

StatisticsData::~StatisticsData()
{
    for (auto c : chartboxes_)
    {
        delete c.second;
    }
}

void StatisticsData::delete_series(
        quint64 chartbox_id,
        quint64 series_index)
{
    qDebug() << "Deleting series " << series_index << " to chartbox id: " << chartbox_id;

    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    it->second->delete_series_by_order_index(series_index);
}

quint64 StatisticsData::add_chartbox(
        DataChartBox* chartbox)
{
    qDebug() << "Adding chartbox with id: " << last_id_;

    quint64 new_id = last_id_++;

    chartboxes_.insert({new_id, chartbox});
    return new_id;
}

void StatisticsData::delete_chartbox(
        quint64 chartbox_id)
{
    qDebug() << "Erasing chartbox with id: " << chartbox_id;

    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    delete it->second;

    chartboxes_.erase(chartbox_id);
}

void StatisticsData::clear_charts(
        quint64 chartbox_id)
{
    qDebug() << "Clearing charts from: " << chartbox_id;

    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    it->second->clear_charts();
}

qreal StatisticsData::axisYMax(
        quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->axisYMax();
}

qreal StatisticsData::axisYMin(
        quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->axisYMin();
}

quint64 StatisticsData::axisXMax(
        quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->axisXMax();
}

quint64 StatisticsData::axisXMin(
        quint64 chartbox_id)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->axisXMin();
}

void StatisticsData::setAxisYMax(
        quint64 chartbox_id,
        qreal axisYMax)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->setAxisYMax(axisYMax);
}

void StatisticsData::setAxisYMin(
        quint64 chartbox_id,
        qreal axisYMin)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->setAxisYMin(axisYMin);
}

void StatisticsData::setAxisXMax(
        quint64 chartbox_id,
        quint64 axisXMax)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->setAxisXMax(axisXMax);
}

void StatisticsData::setAxisXMin(
        quint64 chartbox_id,
        quint64 axisXMin)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    return it->second->setAxisXMin(axisXMin);
}

void StatisticsData::newXValue(
        quint64 chartbox_id,
        quint64 x)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    it->second->newXValue(x);
}

void StatisticsData::save_series_csv(
        quint64 chartbox_id,
        quint64 series_index,
        QString file_name,
        QString data_kind,
        QString chartbox_title,
        QString data_unit,
        QString label)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    save_csv(
        file_name,
        std::vector<QVector<QPointF>>({it->second->get_data(series_index)}),
        QVector<QString>({data_kind}),
        QVector<QString>({chartbox_title}),
        QVector<QString>({data_unit}),
        QVector<QString>({label}));
}

void StatisticsData::save_chartbox_csv(
        quint64 chartbox_id,
        QString file_name,
        QString data_kind,
        QString chartbox_name,
        QString data_unit,
        QVector<QString> label_names)
{
    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    save_csv(
        file_name,
        it->second->get_data(),
        QVector<QString>(label_names.size(), data_kind),
        QVector<QString>(label_names.size(), chartbox_name),
        QVector<QString>(label_names.size(), data_unit),
        label_names);
}

void StatisticsData::save_all_csv(
        QString file_name,
        QVector<quint64> chartbox_order,
        QVector<QString> data_kinds,
        QVector<QString> chartbox_names,
        QVector<QString> data_units,
        QVector<QString> label_names)
{
    std::vector<QVector<QPointF>> datas;

    for (quint64 chartbox_id : chartbox_order)
    {
        auto it = chartboxes_.find(chartbox_id);

        assert(it != chartboxes_.end());

        for (QVector<QPointF> series : it->second->get_data())
        {
            datas.push_back(series);
        }
    }

    save_csv(
        file_name,
        datas,
        data_kinds,
        chartbox_names,
        data_units,
        label_names);
}

void StatisticsData::save_csv(
        const QString& file_name,
        const std::vector<QVector<QPointF>>& datas,
        const QVector<QString>& data_kinds,
        const QVector<QString>& chartbox_names,
        const QVector<QString>& data_units,
        const QVector<QString>& label_names,
        const std::string separator /* = ";"*/)
{
    assert(static_cast<size_t>(data_kinds.size()) == datas.size());
    assert(static_cast<size_t>(chartbox_names.size()) == datas.size());
    assert(static_cast<size_t>(data_units.size()) == datas.size());
    assert(static_cast<size_t>(label_names.size()) == datas.size());

    std::string file_name_ = utils::to_string(file_name);

    // Check if QML format and erase first substring
    if (file_name_.rfind("file://", 0) == 0)
    {
        file_name_.erase(0, 7);
    }

    // Reconversion only for debug propose. This could be erased
    qDebug() << "Storing CSV in file: " << utils::to_QString(file_name_);

    std::map<quint64, std::vector<qreal>> datas_ = merge_datas(datas);

    try
    {
        std::ofstream ofile(file_name_);

        // Headers
        // Datakind
        for (QString kind : data_kinds)
        {
            std::string kind_ = utils::to_string(kind);
            std::replace( kind_.begin(), kind_.end(), ' ', '_');
            ofile << separator << kind_;
        }
        ofile << "\n";

        // Chartbox Title
        for (QString title : chartbox_names)
        {
            std::string title_ = utils::to_string(title);
            std::replace( title_.begin(), title_.end(), ' ', '_');
            ofile << separator << title_;
        }
        ofile << "\n";

        // Data unit
        for (QString unit : data_units)
        {
            std::string unit_ = utils::to_string(unit);
            std::replace( unit_.begin(), unit_.end(), ' ', '_');
            ofile << separator << unit_;
        }
        ofile << "\n";

        // Labels
        ofile << "UnixTime[ms]";

        for (QString label : label_names)
        {
            std::string label_ = utils::to_string(label);
            std::replace( label_.begin(), label_.end(), ' ', '_');
            ofile << separator << label_;
        }
        ofile << "\n";

        // Iterate over all series for a <max_index> times and print values when are available
        for (auto data_it : datas_)
        {
            ofile << data_it.first;
            for (auto series_point : data_it.second)
            {
                ofile << ";";
                // NaN values are not printed
                if (!std::isnan(series_point))
                {
                    ofile << series_point;
                }
            }
            ofile << "\n";
        }
    }
    catch (std::ifstream::failure& e)
    {
        qCritical() << "Error writing CSV with error: "  << e.what();
    }
}

std::map<quint64, std::vector<qreal>> StatisticsData::merge_datas(
        const std::vector<QVector<QPointF>>& datas)
{
    std::map<quint64, std::vector<qreal>> res;

    // Go one by one over the series and add all times in points
    // For each time added in an already time created, add the point and the possible previous points
    // that may not have been in previous series as null
    // For any new time, add all the previous series points as null
    size_t vector_index = 0;
    for (QVector<QPointF> series : datas)
    {
        for (QPointF point : series)
        {
            quint64 x_value = static_cast<unsigned long>(point.rx());

            // Check whether this time has already been added
            auto it = res.find(point.rx());
            if (it == res.end())
            {
                // It is new, so add new vector
                res[x_value] = std::vector<qreal>();
            }

            // Add possible previous values as NaN
            for (size_t i = res[x_value].size(); i < vector_index; i++)
            {
                res[x_value].push_back(std::numeric_limits<double>::quiet_NaN());
            }

            // Add new value
            res[x_value].push_back({point.ry()});
        }
        ++vector_index;
    }

    // Check that all vectors has correct size (vector_index = number of series)
    for (std::map<quint64, std::vector<qreal>>::iterator map_it = res.begin(); map_it != res.end(); map_it++)
    {
        while (map_it->second.size() < vector_index)
        {
            map_it->second.push_back(std::numeric_limits<double>::quiet_NaN());
        }
    }

    return res;
}
