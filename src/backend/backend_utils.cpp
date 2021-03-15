
#include <include/utils.h>
#include <include/backend/backend_types.h>
#include <include/model/model_types.h>

namespace backend{

QString id_to_QString(const EntityId id)
{
    return utils::to_QString(id);
}

QString get_name(const EntityId id)
{
    // TODO
    return id_to_QString(id);
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
