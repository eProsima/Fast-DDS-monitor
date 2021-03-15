#ifndef FASTDDS_MONITOR_BACKEND_TYPES_H
#define FASTDDS_MONITOR_BACKEND_TYPES_H

#include <QString>

#include <core/types/types.hpp>

namespace backend {

typedef eprosima::fastdds::dds::statistics::EntityId EntityId;
typedef eprosima::fastdds::dds::statistics::EntityType EntityType;

#define ALL_ID_BACKEND "-1"

} //namespace backend

#endif // FASTDDS_MONITOR_BACKEND_TYPES_H
