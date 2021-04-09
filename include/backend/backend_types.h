#ifndef FASTDDS_MONITOR_BACKEND_TYPES_H
#define FASTDDS_MONITOR_BACKEND_TYPES_H

#include <QString>

#include <fastdds-statistics-backend/types/types.hpp>

namespace backend {

using EntityId = eprosima::statistics_backend::EntityId;
using EntityKind = eprosima::statistics_backend::EntityKind;
using DataKind = eprosima::statistics_backend::DataKind;
using StatisticKind = eprosima::statistics_backend::StatisticKind;
using EntityInfo = eprosima::statistics_backend::Info;

extern const EntityId ID_ALL;
extern const EntityId ID_NONE;

} //namespace backend

#endif // FASTDDS_MONITOR_BACKEND_TYPES_H
