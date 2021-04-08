#ifndef FASTDDS_MONITOR_CALLBACK_H
#define FASTDDS_MONITOR_CALLBACK_H

#include <include/backend/backend_types.h>

namespace backend {

struct Callback
{
    Callback()
    {}

    Callback(backend::EntityId new_entity, backend::EntityKind new_entity_kind)
        : new_entity(new_entity)
        , new_entity_kind(new_entity_kind)
    {}

    backend::EntityId new_entity;
    backend::EntityKind new_entity_kind;
};

}

#endif // FASTDDS_MONITOR_CALLBACK_H
