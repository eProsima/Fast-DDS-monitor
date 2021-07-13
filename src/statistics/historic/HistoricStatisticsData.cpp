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
