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
 * @file csv.h
 * @brief collection of csv in/out functions
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_IO_CSV_H
#define _EPROSIMA_FASTDDS_MONITOR_IO_CSV_H

#include <fstream>
#include <string>
#include <vector>

#include <QPointF>
#include <QString>
#include <QVector>

namespace io {

//! Class that handles the CSV in and out functions
class HandlerCSV
{

public:

    /**
     * TODO
     *
     * @warning Assumes the size of the vectors and datas are coherent
     */
    static bool write_series_to_csv(
        const QString& file_name,
        const std::vector<QVector<QPointF>>& datas,
        const QVector<QString>& data_kinds,
        const QVector<QString>& chartbox_names,
        const QVector<QString>& label_names,
        const std::vector<std::string>& data_units);

protected:

    //! TODO
    static bool write_csv(
        const std::string& file_name,
        const std::vector<std::vector<std::string>>& headers,
        const std::vector<std::vector<double>>& data,
        const std::string separator = ";");

    //! TODO
    static std::map<quint64, std::vector<qreal>> merge_datas(
        const std::vector<QVector<QPointF>>& datas);

    //! TODO
    static std::vector<std::vector<double>> to_csv_data(
        const std::map<quint64, std::vector<qreal>>& data_map);

    //! TODO
    static std::string double_to_string(double data);

};

} //namespace io

#endif // _EPROSIMA_FASTDDS_MONITOR_IO_CSV_H
