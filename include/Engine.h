#ifndef ENGINE_H
#define ENGINE_H

#include <QQmlApplicationEngine>

#include <include/backend/SyncBackendConnection.h>
#include <include/backend/Listener.h>
#include <include/model/SubListedListModel.h>
#include <include/model/tree/TreeModel.h>
#include <include/statistics/StatisticsData.h>

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

    // TODO eliminate models in args as they are private values in class
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
    bool fill_dds_data(backend::EntityId id = ALL_ID_BACKEND);

    // Update the model with a new or updated entity
    bool update_participant_data(models::ListModel* dds_model, backend::EntityId id);
    bool update_endpoint_data(models::ListModel* dds_model, backend::EntityId id);

    // QoS DATA
    // Retrieve the QoS information. With ALL or incorrect ID it
    // returns an empty QoS Configuration
    bool fill_dds_info(backend::EntityId id = ALL_ID_BACKEND);

    // Statistic summary DATA
    // Retrieve the QoS information. With ALL or incorrect ID it
    // returns an empty QoS Configuration
    bool fill_summary(backend::EntityId id = ALL_ID_BACKEND);

    // ON CLICKED
    // Update by click functions
    bool on_dds_entity_clicked(backend::EntityId id);
    bool on_entity_clicked(backend::EntityId id);

    bool onSelectedEntityKind(
            backend::EntityKind entityKind,
            QString entityModelId);

    bool onAddStatisticsDataSeries(
            backend::DataKind dataKind,
            backend::EntityId sourceEntityId,
            backend::EntityId targetEntityId,
            quint16 bins,
            quint64 startTime,
            bool startTimeDefault,
            quint64 endTime,
            bool endTimeDefault,
            backend::StatisticKind statisticKind);

protected:
    Engine();

    ~Engine();

    // Fill a Physical Model from scratch getting all systems and their subentities
    bool fill_physical_data(models::ListModel* physical_model);

    // Fill a Logical Model from scratch getting all systems and their subentities
    bool fill_logical_data(models::ListModel* logical_model);

    bool fillAvailableEntityIdList(backend::EntityKind entityKind, QString entityModelId);

    static bool update_tree_model(models::TreeModel* old_model, const json& data);
    static models::TreeModel* entity_info(backend::EntityId id = ALL_ID_BACKEND);

private:

    bool enabled_;

    backend::Listener* listener_;

    models::ListModel* participantsModel_;
    models::ListModel* physicalModel_;
    models::ListModel* logicalModel_;

    models::TreeModel* infoModel_;
    models::TreeModel* summaryModel_;

    models::ListModel* entityIdModelFirst_;
    models::ListModel* entityIdModelSecond_;

    StatisticsData* statisticsData_;

    backend::SyncBackendConnection backend_connection_;
};

#endif // ENGINE_H
