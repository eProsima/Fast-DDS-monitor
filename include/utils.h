#ifndef FASTDDS_MONITOR_UTILS_H
#define FASTDDS_MONITOR_UTILS_H

#include <QString>
#include <string>

namespace utils {

QString to_QString(std::string st);

std::string to_string(QString st);

} //namespace utils

#endif // FASTDDS_MONITOR_UTILS_H
