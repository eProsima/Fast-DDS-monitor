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
#include <ctime>
#include <math.h>
#include <sys/time.h>
#include <time.h>

#include <fastdds-monitor/utils.h>

namespace utils {

QString to_QString(
        std::string st)
{
    return QString::fromUtf8(st.c_str());
}

std::string to_string(
        QString st)
{
    return st.toUtf8().constData();
}

std::string now(
        bool miliseconds /* = true */)
{
    char buffer[24]; // YYYY:MM:DD HH:MM:SS + '\0' <= 24
    char ms_buffer[32]; // YYYY:MM:DD HH:MM:SS.mmm + '\0' <= 32
    unsigned short millisec;
    struct tm* tm_info;
    struct timeval tv;

    gettimeofday(&tv, NULL);

    tm_info = localtime(&tv.tv_sec);

    strftime(buffer, sizeof (buffer), "%Y:%m:%d %H:%M:%S", tm_info);

    if (miliseconds)
    {
        millisec = lrint(tv.tv_usec / 1000.0); // Round to nearest millisec
        if (millisec >= 1000) // Allow for rounding up to nearest second
        {
            millisec -= 1000;
            tv.tv_sec++;
        }

        snprintf(ms_buffer, sizeof(ms_buffer), "%s.%03d", buffer, millisec);
    }
    else
    {
        return buffer;
    }

    return ms_buffer;
}

} //namespace utils
