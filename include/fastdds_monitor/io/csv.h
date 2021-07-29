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
     * Write down several series with the headers and their respective data in the format:
     *
     *          ; <data_kind       series1> ; <data_kind          series2> ; ...
     *          ; <chartbox_names  series1> ; <chartbox_names     series2> ; ...
     * ms       ; <data_units      series1> ; <data_units         series2> ; ...
     * UnixTime ; <label_names     series1> ; <label_names        series2> ; ...
     * <time0>  ; <data0           series1> ; <data1              series2> ; ...
     * <time1>  ;                           ; <data1              series2> ; ...
     * <time2>  ; <data0           series1> ;                              ; ...
     *
     * Details:
     * - Every data value is double, included time
     * - No ; at the final of the row
     * - No spaces before or after ;
     *
     * @warning Assumes the size of the vectors and datas are coherent
     */
    static bool write_series_to_csv(
            const QString& file_name,
            const std::vector<QVector<QPointF>>& datas,
            const QStringList& data_kinds,
            const QStringList& chartbox_names,
            const QStringList& label_names,
            const std::vector<std::string>& data_units);

protected:

    /**
     * Write down the headers and the data in a new csv file
     *
     * @param file_name path and name of the csv file
     * @param headers   each row of headers + each column per row
     * @param data      each row of data + each column per row
     * @param separator csv separator for each data
     *
     * @warning headers coluumns must be equal to data columns
     *
     * @return true if success, false otherwise
     */
    static bool write_csv(
            const std::string& file_name,
            const std::vector<std::vector<std::string>>& headers,
            const std::vector<std::vector<double>>& data,
            const std::string separator = ";");

    /**
     * Merge several data so the ones that shares time are joined in the same key
     * For those data that do not have value for a specific key, a NaN is added
     *
     * @return map with the data merged
     */
    static std::map<quint64, std::vector<qreal>> merge_datas(
            const std::vector<QVector<QPointF>>& datas);

    //! Transform a map of merged datas on a matrix available to write in a csv
    static std::vector<std::vector<double>> to_csv_data(
            const std::map<quint64, std::vector<qreal>>& data_map);

};

} //namespace io

#endif // _EPROSIMA_FASTDDS_MONITOR_IO_CSV_H
