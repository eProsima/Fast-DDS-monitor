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

#include <QDebug>

#include <fastdds_monitor/statistics/historic/HistoricDataChartBox.h>
#include <fastdds_monitor/statistics/historic/HistoricStatisticsData.h>

QtCharts::QVXYModelMapper* HistoricStatisticsData::add_series(
        quint64 chartbox_id,
        QVector<QPointF> new_series)
{
    qDebug() << "Adding historic serie to chartbox id: " << chartbox_id;

    auto it = chartboxes_.find(chartbox_id);

    assert(it != chartboxes_.end());

    HistoricDataChartBox* h_chartbox = dynamic_cast<HistoricDataChartBox*>(it->second);

    return h_chartbox->add_series(new_series);
}

quint64 HistoricStatisticsData::add_chartbox(
        QString data_kind)
{
    return StatisticsData::add_chartbox(new HistoricDataChartBox(data_kind));
}
