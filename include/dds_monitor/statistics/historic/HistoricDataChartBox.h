// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima DDS Monitor.
//
// eProsima DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

/**
 * @file HistoricDataChartBox.hpp
 */

#ifndef _EPROSIMA_DDS_MONITOR_STATISTICS_HISTORIC_HISTORICDATACHARTBOX_H
#define _EPROSIMA_DDS_MONITOR_STATISTICS_HISTORIC_HISTORICDATACHARTBOX_H

#include <limits>
#include <mutex>

#include <QtCharts/QVXYModelMapper>

#include <dds_monitor/statistics/DataChartBox.h>

/**
 * @brief main panel Chartbox that contains Historic Series
 */
class HistoricDataChartBox : public DataChartBox
{

public:

    using DataChartBox::DataChartBox;

    //! Add new series
    QVXYModelMapper* add_series(
            QVector<QPointF> new_series);
};

#endif // _EPROSIMA_DDS_MONITOR_STATISTICS_HISTORIC_HISTORICDATACHARTBOX_H
