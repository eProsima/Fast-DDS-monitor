
#include <include/utils.h>
#include <include/backend/backend_types.h>
#include <include/model/model_types.h>

#include <fastdds-statistics-backend/StatisticsBackend.hpp>

namespace backend{

QString id_to_QString(const EntityId id)
{
    return utils::to_QString(id);
}

EntityId models_id_to_backend_id(const models::EntityId id)
{
    return EntityId(id.toUtf8());
}

QString get_name(const EntityId id)
{
    return utils::to_QString(
                eprosima::statistics_backend::StatisticsBackend::get_info(id)["name"]);
}

// PROCESS
QString process_pid(backend::EntityId process_id)
{
    // TODO
    return id_to_QString(process_id);
}

// DDS GUID
QString entity_guid(backend::EntityId id)
{
    // TODO
   return id_to_QString(id);
}

// TOPIC
QString topic_type(backend::EntityId id)
{
    // TODO
    return id_to_QString(id);
}

} //namespace backend
