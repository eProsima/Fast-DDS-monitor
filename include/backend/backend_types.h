#ifndef FASTDDS_MONITOR_BACKEND_TYPES_H
#define FASTDDS_MONITOR_BACKEND_TYPES_H

#include <QString>

#include <fastdds-statistics-backend/types/types.hpp>

namespace backend {

typedef eprosima::statistics_backend::EntityId EntityId;
typedef eprosima::statistics_backend::EntityKind EntityKind;
typedef eprosima::statistics_backend::DataKind DataKind;
typedef eprosima::statistics_backend::StatisticKind StatisticKind;

#define ALL_ID_BACKEND "-1"

} //namespace backend

#endif // FASTDDS_MONITOR_BACKEND_TYPES_H
