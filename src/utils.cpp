
#include <chrono>
#include <ctime>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#include <include/utils.h>

namespace utils {

QString to_QString(std::string st)
{
    return QString::fromUtf8(st.c_str());
}

std::string to_string(QString st)
{
    return st.toUtf8().constData();
}

std::string now(bool miliseconds /* = true */)
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
        millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec
        if (millisec>=1000) { // Allow for rounding up to nearest second
          millisec -=1000;
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
