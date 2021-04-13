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
    {
    }

    static bool set_listener(Listener* listener);
    static bool unset_listener();

    static bool update_physical_data(models::ListModel* physical_model);
    static bool update_logical_data(models::ListModel* logical_model);
    static bool update_dds_data(models::ListModel* dds_model, EntityId id);
    static bool update_get_data_dialog_entity_id(models::ListModel* entity_model, EntityKind entity_kind);

    static bool update_host_data(ListItem* host_item);
    static bool update_user_data(ListItem* user_item);
    static bool update_process_data(ListItem* process_item);

    static bool update_domain_data(ListItem* domain_item);
    static bool update_topic_data(ListItem* topic_item);

    static bool update_participant_data(ListItem* participant_item);
    static bool update_endpoint_data(ListItem* endpoint_item);
    static bool update_locator_data(ListItem* locator_item);

    static bool update_entity_id_data(ListItem* entity_item);

    static EntityId init_monitor(int domain);
    static EntityId init_monitor(QString locators);

    static json get_info(EntityId id);
    static json get_summary(backend::EntityId id);
    static std::string get_name(backend::EntityId id);

    static std::vector<backend::StatisticsData> get_data(
            DataKind data_kind,
            EntityId source_entity_id,
            EntityId target_entity_id,
            uint16_t bins,
            Timestamp start_time,
            Timestamp end_time,
            StatisticKind statistic_kind);

protected:

    static ListItem* create_process_data_(backend::EntityId id);
    static ListItem* create_user_data_(backend::EntityId id);
    static ListItem* create_host_data_(backend::EntityId id);

    static ListItem* create_domain_data_(backend::EntityId id);
    static ListItem* create_topic_data_(backend::EntityId id);

    static ListItem* create_participant_data_(backend::EntityId id);
    static ListItem* create_endpoint_data_(backend::EntityId id);
    static ListItem* create_locator_data_(backend::EntityId id);

    static ListItem* create_entity_id_data_(backend::EntityId id);

    static bool update_entity_data_(
            SubListedListItem* item,
            backend::EntityKind type,
            bool (*update_function)(ListItem*),
            ListItem* (*create_function)(backend::EntityId));

    static bool update_model_data_(
            ListModel* model,
            EntityKind type,
            EntityId id,
            bool (*update_function)(ListItem*),
            ListItem* (*create_function)(EntityId));

};

} //namespace backend

#endif // FASTDDS_MONITOR_BACKENDCONNECTION_H
