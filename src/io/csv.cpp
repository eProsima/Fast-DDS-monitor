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

#include <cmath>

#include <fastdds_monitor/io/csv.h>
#include <fastdds_monitor/utils.h>

namespace io {

bool HandlerCSV::write_series_to_csv(
        const QString& file_name,
        const std::vector<QVector<QPointF>>& datas,
        const QStringList& data_kinds,
        const QStringList& chartbox_names,
        const QStringList& label_names,
        const std::vector<std::string>& data_units)
{
    /////
    // CREATE FILE NAME
    std::string file_name_ = utils::to_string(file_name);

    // Check if QML format and erase first substring dependeing on SO
    if (file_name_.rfind("file:///", 0) == 0)
    {
#ifdef _WIN32
        file_name_.erase(0, 8);
#else
        file_name_.erase(0, 7);
#endif // ifdef _WIN32
    }

    /////
    // CREATE CSV DATA
    // Merge every data in a map
    std::map<quint64, std::vector<qreal>> data_map = merge_datas(datas);

    // Convert map data to csv format
    std::vector<std::vector<double>> csv_data = to_csv_data(data_map);

    /////
    // CREATE HEADERS
    int size = data_kinds.size();

    // Empty data to export
    if (size <= 0)
    {
        return false;
    }

    // Total size is 1 more for time column
    std::vector<std::vector<std::string>> headers(4, std::vector<std::string>(size + 1));

    // Headers: <void>, dataKind, chartbox name, data unit, series label
    for (int i = 0; i < size; ++i)
    {
        headers[0][i + 1] = utils::to_string(data_kinds[i]);
        headers[1][i + 1] = utils::to_string(chartbox_names[i]);
        headers[2][i + 1] = data_units[i];
        headers[3][i + 1] = utils::to_string(label_names[i]);
    }

    // Fill time column in data units and label
    headers[2][0] = "ms";
    headers[3][0] = "UnixTime";

    /////
    // WRITE IN FILE
    return write_csv(file_name_, headers, csv_data);
}

bool HandlerCSV::write_csv(
        const std::string& file_name,
        const std::vector<std::vector<std::string>>& headers,
        const std::vector<std::vector<double>>& data,
        const std::string separator /* = ";"" */)
{
    try
    {
        std::ofstream ofile(file_name);

        // Headers
        for (const std::vector<std::string>& header_row : headers)
        {
            if (header_row.size() > 0)
            {
                ofile << header_row[0]; // first value print outside the loop to avoid last separator
                for (auto it = std::next(header_row.begin()); it != header_row.end(); ++it)
                {
                    ofile << separator << *it;
                }
            }
            ofile << "\n";
        }

        // Data
        ofile << std::fixed; // Do not use scientific notation for double
        for (const std::vector<double>& data_row : data)
        {
            if (data_row.size() > 0)
            {
                ofile << utils::double_to_string(data_row[0]); // first value print outside the loop to avoid last separator
                for (auto it = std::next(data_row.begin()); it != data_row.end(); ++it)
                {
                    ofile << separator << utils::double_to_string(*it);
                }
            }
            ofile << "\n";
        }

        ofile.close();
    }
    catch (std::ifstream::failure& e)
    {
        qCritical() << "Error writing CSV with error: "  << e.what();
        return false;
    }

    return true;
}

std::map<quint64, std::vector<qreal>> HandlerCSV::merge_datas(
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

std::vector<std::vector<double>> HandlerCSV::to_csv_data(
        const std::map<quint64, std::vector<qreal>>& data_map)
{
    size_t rows = data_map.size();
    size_t cols = 0;

    // In case there are not rows, return a void vector
    if (rows)
    {
        cols = data_map.begin()->second.size();
    }

    std::vector<std::vector<double>> csv_data(rows, std::vector<double>(cols + 1));

    size_t i = 0;
    size_t j = 0;
    for (std::pair<quint64, std::vector<qreal>> it : data_map)
    {
        j = 0;
        csv_data[i][j++] = it.first;
        for (const qreal data : it.second)
        {
            csv_data[i][j++] = data;
        }

        ++i;
    }

    return csv_data;
}

} //namespace io
