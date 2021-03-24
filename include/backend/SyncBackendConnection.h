#ifndef FASTDDS_MONITOR_BACKENDCONNECTION_H
#define FASTDDS_MONITOR_BACKENDCONNECTION_H

#include <include/model/SubListedListModel.h>

#include <include/model/physical/HostModelItem.h>
#include <include/model/physical/UserModelItem.h>
#include <include/model/physical/ProcessModelItem.h>
#include <include/model/logical/DomainModelItem.h>
#include <include/model/logical/TopicModelItem.h>

#include <fastdds-statistics-backend/StatisticsBackend.hpp>
#include <include/backend/backend_types.h>
#include <include/backend/Listener.h>

#include <include/model/tree/TreeModel.h>

namespace backend {

using namespace models;
using nlohmann::json;

class SyncBackendConnection
{
public:
    SyncBackendConnection()
    {}

    static bool set_listener(Listener* listener);
    static bool unset_listener();

    static bool update_physical_data(models::ListModel* physical_model);
    static bool update_logical_data(models::ListModel* logical_model);
    static bool update_dds_data(models::ListModel* dds_model, EntityId id);
    static bool updateGetDataDialogEntityId(models::ListModel* entityModel, EntityKind entityKind);

    static bool update_host_data(ListItem* host_item);
    static bool update_user_data(ListItem* user_item);
    static bool update_process_data(ListItem* process_item);

    static bool update_domain_data(ListItem* domain_item);
    static bool update_topic_data(ListItem* topic_item);

    static bool update_participant_data(ListItem* participant_item);
    static bool update_endpoint_data(ListItem* endpoint_item);
    static bool update_locator_data(ListItem* locator_item);

    static bool updateEntityIdData(ListItem* entityItem);

    static bool init_monitor(int domain);
    static bool init_monitor(QString locators);

    static json get_info(EntityId id);
    static json get_summary(backend::EntityId id);

protected:

    static ListItem* _create_process_data(backend::EntityId id);
    static ListItem* _create_user_data(backend::EntityId id);
    static ListItem* _create_host_data(backend::EntityId id);

    static ListItem* _create_domain_data(backend::EntityId id);
    static ListItem* _create_topic_data(backend::EntityId id);

    static ListItem* _create_participant_data(backend::EntityId id);
    static ListItem* _create_endpoint_data(backend::EntityId id);
    static ListItem* _create_locator_data(backend::EntityId id);

    static ListItem* _createEntityIdData(backend::EntityId id);

    static bool __update_entity_data(
            SubListedListItem* item,
            backend::EntityKind type,
            bool (*update_function)(ListItem*),
            ListItem* (*create_function)(backend::EntityId));

    static bool __update_model_data(
            ListModel* model,
            EntityKind type,
            EntityId id,
            bool (*update_function)(ListItem*),
            ListItem* (*create_function)(EntityId));

};

} //namespace backend

#endif // FASTDDS_MONITOR_BACKENDCONNECTION_H
