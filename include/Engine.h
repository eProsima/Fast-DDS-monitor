#ifndef ENGINE_H
#define ENGINE_H

#include <QQmlApplicationEngine>

#include <include/backend/SyncBackendConnection.h>
#include <include/model/SubListedListModel.h>

#include <include/model/tree/TreeModel.h>

class Engine : public QQmlApplicationEngine
{
public:

    static Engine* get_instance(){
        static Engine instance;
        return &instance;
    }

    QObject* enable();

    void init_monitor(int domain);
    void init_monitor(QString locators);

    // PHYSICAL PARTITION
    // Update the model with a new or updated entity
    bool update_host_data(models::ListModel* physical_model, backend::EntityId id);
    bool update_user_data(models::ListModel* physical_model, backend::EntityId id);
    bool update_process_data(models::ListModel* physical_model, backend::EntityId id);

    // LOGICAL PARTITION
    // Update the model with a new or updated entity
    bool update_domain_data(models::ListModel* logical_model, backend::EntityId id);
    bool update_topic_data(models::ListModel* logical_model, backend::EntityId id);

    // DDS PARTITION
    // Fill a DDS Model from scratch getting the participants from the id and its subentities
    bool fill_dds_data(models::ListModel* dds_model, backend::EntityId id = ALL_ID_BACKEND);

    // Update the model with a new or updated entity
    bool update_participant_data(models::ListModel* dds_model, backend::EntityId id);
    bool update_endpoint_data(models::ListModel* dds_model, backend::EntityId id);

    // QoS DATA
    // Retrieve the QoS information. With ALL or incorrect ID it
    // returns an empty QoS Configuration
    bool fill_dds_qos(backend::EntityId id = ALL_ID_BACKEND);

protected:
    Engine();

    // Fill a Physical Model from scratch getting all systems and their subentities
    bool fill_physical_data(models::ListModel* physical_model);

    // Fill a Logical Model from scratch getting all systems and their subentities
    bool fill_logical_data(models::ListModel* logical_model);

    static bool update_tree_model(models::TreeModel* old_model, const json& data);
    static models::TreeModel* entity_qos(backend::EntityId id = ALL_ID_BACKEND);

private:
    models::ListModel* participantsModel;
    models::ListModel* physicalModel;
    models::ListModel* logicalModel;

    models::TreeModel* qosModel;

    backend::SyncBackendConnection backend_connection;
};

#endif // ENGINE_H
