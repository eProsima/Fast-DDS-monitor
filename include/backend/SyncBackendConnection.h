#ifndef FASTDDS_MONITOR_BACKENDCONNECTION_H
#define FASTDDS_MONITOR_BACKENDCONNECTION_H

#include <include/model/SubListedListModel.h>

#include <include/model/physical/HostModelItem.h>
#include <include/model/physical/UserModelItem.h>
#include <include/model/physical/ProcessModelItem.h>
#include <include/model/logical/DomainModelItem.h>
#include <include/model/logical/TopicModelItem.h>

#include <core/StatisticsBackend.hpp>
#include <include/backend/backend_types.h>

namespace backend {

using namespace models;

class SyncBackendConnection
{
public:
    SyncBackendConnection()
    {}

    // Those functions will not be static in case in the futute we want the SyncBackendConnection to store some Data from Backend
    static eprosima::fastdds::dds::statistics::StatisticsBackend* backend_object()
    {
        return eprosima::fastdds::dds::statistics::StatisticsBackend::get_instance();
    }

    // PHYSICAL PARTITION
    // Fill a Physical Model from scratch getting all systems and their subentities
    bool fill_physical_data(models::ListModel* physical_model);

    // Update the model with a new or updated entity
    bool update_host_data(models::ListModel* physical_model, EntityId id);
    bool update_user_data(models::ListModel* physical_model, EntityId id);
    bool update_process_data(models::ListModel* physical_model, EntityId id);

    // LOGICAL PARTITION
    // Fill a Logical Model from scratch getting all systems and their subentities
    bool fill_logical_data(models::ListModel* logical_model);

    // Update the model with a new or updated entity
    bool update_domain_data(models::ListModel* logical_model, EntityId id);
    bool update_topic_data(models::ListModel* logical_model, EntityId id);

    // DDS PARTITION
    // Fill a DDS Model from scratch getting the participants from the id and its subentities
    bool fill_dds_data(models::ListModel* dds_model, EntityId id = ALL_ID_BACKEND);

    // Update the model with a new or updated entity
    bool update_participant_data(models::ListModel* dds_model, EntityId id);
    bool update_endpoint_data(models::ListModel* dds_model, EntityId id);

protected:
    static bool _update_physical_data(models::ListModel* physical_model);
    static bool _update_logical_data(models::ListModel* logical_model);
    static bool _update_dds_data(models::ListModel* dds_model, EntityId id);

    static bool _update_host_data(ListItem* host_item);
    static bool _update_user_data(ListItem* user_item);
    static bool _update_process_data(ListItem* process_item);

    static bool _update_domain_data(ListItem* domain_item);
    static bool _update_topic_data(ListItem* topic_item);

    static bool _update_participant_data(ListItem* participant_item);
    static bool _update_endpoint_data(ListItem* endpoint_item);

    static ListItem* _create_process_data(backend::EntityId id);
    static ListItem* _create_user_data(backend::EntityId id);
    static ListItem* _create_host_data(backend::EntityId id);

    static ListItem* _create_domain_data(backend::EntityId id);
    static ListItem* _create_topic_data(backend::EntityId id);

    static ListItem* _create_participant_data(backend::EntityId id);
    static ListItem* _create_endpoint_data(backend::EntityId id);

    static bool __update_entity_data(
            SubListedListItem* item,
            backend::EntityType type,
            bool (*update_function)(ListItem*),
            ListItem* (*create_function)(backend::EntityId));

    static bool __update_model_data(
            ListModel* model,
            EntityType type,
            EntityId id,
            bool (*update_function)(ListItem*),
            ListItem* (*create_function)(EntityId));

};

} //namespace backend

#endif // FASTDDS_MONITOR_BACKENDCONNECTION_H
