#ifndef FASTDDS_MONITOR_UTILS_H
#define FASTDDS_MONITOR_UTILS_H

#include <QHash>
#include <QString>
#include <string>

namespace utils {

QString to_QString(std::string st);

std::string to_string(QString st);

std::string now(bool miliseconds = true);

} //namespace utils

// // This is required to use QString as a key in maps
// // WARNING : this must be commented to compile in QtCreator, and uncommented to compile with CMake
// namespace std {
// template<> struct hash<QString> {
//   std::size_t operator()(const QString& s) const noexcept {
//     return (size_t) qHash(s);
//   }
// };
// }


#endif // FASTDDS_MONITOR_UTILS_H
