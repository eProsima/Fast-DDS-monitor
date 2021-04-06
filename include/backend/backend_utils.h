#ifndef FASTDDS_MONITOR_BACKEND_UTILS_H
#define FASTDDS_MONITOR_BACKEND_UTILS_H

#include <QString>
#include <string>

#include <include/model/model_types.h>
#include <include/utils.h>
#include <include/backend/backend_types.h>
#include <json.hpp>

namespace backend{

QString id_to_QString(const EntityId id);

EntityId models_id_to_backend_id(const models::EntityId id);

QString get_name(const EntityId id);

// PROCESS
QString process_pid(backend::EntityId process_id);

// DDS GUID
QString entity_guid(backend::EntityId id);

// TOPIC
QString topic_type(backend::EntityId id);


backend::EntityKind stringToEntityKind(
        const QString& entityKind);

backend::DataKind stringToDataKind(
       const QString& dataKind);

backend::StatisticKind stringToStatisticKind(
       const QString& statisticKind);

} //namespace backend

#endif // FASTDDS_MONITOR_BACKEND_UTILS_H
