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

#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>

#include <fastdds_monitor/utils.h>

namespace utils {

QString to_QString(
        std::string& st)
{
    return QString::fromUtf8(st.c_str());
}

QString to_QString(
        const std::string& st)
{
    return QString::fromUtf8(st.c_str());
}

std::string to_string(
        QString& st)
{
    return st.toUtf8().constData();
}

std::string to_string(
        const QString& st)
{
    return st.toUtf8().constData();
}

std::string now(
        bool miliseconds /* = true */)
{

    auto now = std::chrono::system_clock::now();
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    msec %= 1000;

    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;

#ifdef _WIN32
    struct tm now_tm;
    _localtime64_s(&now_tm, &now_time_t);
    ss << std::put_time(&now_tm, "%Y-%m-%d %X");
#else
    ss << std::put_time(localtime(&now_time_t), "%Y-%m-%d %X");
#endif // ifdef _WIN32

    if (miliseconds)
    {
        ss << "." << std::setw(3) << std::setfill('0') << msec;
    }

    return ss.str();
}

std::string double_to_string(
        const double& d)
{
    // Check if it is NaN
    if (!std::isnan(d))
    {
        std::string str = std::to_string(d);
        // Ensure that there is a decimal point in the resulting string
        if (str.find('.') != std::string::npos)
        {
            // Remove trailing zeros
            str.erase(str.find_last_not_of('0') + 1, std::string::npos);

            // Remove the decimal point in case it is the last element of the string
            if (str.find('.') == str.size() - 1)
            {
                str = str.substr(0, str.size() - 1);
            }
        }

        return str;
    }
    else
    {
        return "";
    }
}

QStringList to_QStringList(
        const std::vector<std::string>& vector)
{
    QStringList string_list;
    string_list.reserve(static_cast<int>(vector.size()));
    for (size_t i = 0; i < vector.size(); i++)
    {
        string_list << to_QString(vector[i]);
    }

    return string_list;
}

std::string erase_file_substr(
        const QString& st)
{
    std::string file = to_string(st);
    // Check if QML format and erase first substring dependeing on SO
    if (file.rfind("file://", 0) == 0)
    {
#ifdef _WIN32
        file.erase(0, 8);
#else
        file.erase(0, 7);
#endif // ifdef _WIN32
    }
    return file;
}

} //namespace utils
