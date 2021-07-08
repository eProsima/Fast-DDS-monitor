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
 * @file HistoricDataChartBox.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_STATISTICS_HISTORIC_HISTORICDATACHARTBOX_H
#define _EPROSIMA_FASTDDS_MONITOR_STATISTICS_HISTORIC_HISTORICDATACHARTBOX_H

#include <limits>
#include <mutex>

#include <QtCharts/QVXYModelMapper>

#include <fastdds_monitor/statistics/DataChartBox.h>

/**
 * TODO
 */
class HistoricDataChartBox : public DataChartBox
{

public:

    using DataChartBox::DataChartBox;

    //! Add new series
    QtCharts::QVXYModelMapper* add_series(
        QVector<QPointF> new_series);
};

#endif // _EPROSIMA_FASTDDS_MONITOR_STATISTICS_HISTORIC_HISTORICDATACHARTBOX_H
