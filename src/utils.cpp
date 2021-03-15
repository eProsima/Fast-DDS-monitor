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

} //namespace utils
