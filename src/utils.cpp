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

} //namespace utils
