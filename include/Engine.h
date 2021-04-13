#ifndef ENGINE_H
#define ENGINE_H

#include <QQmlApplicationEngine>
#include <QRecursiveMutex>
#include <QQueue>
#include <QWaitCondition>
#include <QThread>

#include <atomic>

#include <include/backend/SyncBackendConnection.h>
#include <include/backend/Listener.h>
#include <include/backend/Callback.h>
#include <include/model/SubListedListModel.h>
#include <include/model/tree/TreeModel.h>
#include <include/statistics/StatisticsData.h>
#include <include/CallbackListener.h>

class Engine : public QQmlApplicationEngine
{
public:

    static Engine* get_instance()
    {
        static Engine instance;
        return &instance;
    }

    QObject* enable();

    void init_monitor(int domain);
    void init_monitor(QString locators);

    // TODO eliminate models in args as they are private values in class
    // PHYSICAL PARTITION
    // Update the model with a new or updated entity
    bool update_host_data(backend::EntityId id);
    bool update_user_data(backend::EntityId id);
    bool update_process_data(backend::EntityId id);

    // LOGICAL PARTITION
    // Update the model with a new or updated entity
    bool update_domain_data(backend::EntityId id);
    bool update_topic_data(backend::EntityId id);

    // DDS PARTITION
    // Fill a DDS Model getting the participants related with <id> and its subentities
    // With ID_NONE
    bool update_dds_data(backend::EntityId id);
    // Fill a DDS Model as <fill_dds_data> but reseting the previous model
    bool update_reset_dds_data(backend::EntityId id);

    // Update the model with a new or updated entity
    bool update_participant_data(backend::EntityId id);
    bool update_endpoint_data(backend::EntityId id);
    bool update_locator_data(backend::EntityId id);

    // QoS DATA
    // Retrieve the QoS information. With ALL or incorrect ID it
    // returns an empty QoS Configuration
    bool fill_entity_info(backend::EntityId id = backend::ID_ALL);

    // Statistic summary DATA
    // Retrieve the QoS information. With ALL or incorrect ID it
    // returns an empty QoS Configuration
    bool fill_summary(backend::EntityId id = backend::ID_ALL);

    // Remove the Issue model and creates a new one by the json structure stored in <issue_info_>
    bool fill_issue();

    // Add to Issue Model a callback or an issue
    bool add_issue_callback(std::string callback, std::string time);
    bool add_issue_issue(std::string issue);

    // ON CLICKED
    // Update by click functions
    bool entity_clicked(backend::EntityId id, backend::EntityKind kind);

    bool on_selected_entity_kind(
            backend::EntityKind entity_kind,
            QString entity_model_id);

    bool on_add_statistics_data_series(
            backend::DataKind data_kind,
            backend::EntityId source_entity_id,
            backend::EntityId target_entity_id,
            quint16 bins,
            quint64 start_time,
            bool start_time_default,
            quint64 end_time,
            bool end_time_default,
            backend::StatisticKind statistic_kind);

    bool add_callback(backend::Callback callback);

    void refresh_engine();

    // Get all callbacks from the queue and process each of them
    void process_callback_queue();

signals:
    void callback_added();

protected:
    Engine();

    ~Engine();

    // Fill a Physical Model getting all systems and their subentities
    bool fill_physical_data();

    // Fill a Logical Model getting all hosts and their subentities
    bool fill_logical_data();

    // Fill a DDS Model getting all participants related with the <last_clicked_entity> and their subentities
    bool fill_dds_data();

    bool fill_available_entity_id_list(backend::EntityKind entity_kind, QString entity_model_id);

    static bool update_tree_model(models::TreeModel* old_model, const json& data);
    static models::TreeModel* entity_info(backend::EntityId id = backend::ID_ALL);

    void shared_init_monitor_(backend::EntityId domain_id);

    // True if there are callbacks in the queue. It is useful to get the mutex and ask
    bool are_callbacks_to_process_();

    // Pops one callback from callbacks queue and process it
    bool process_callback_();

    // Applies the changes to models of one callback
    bool read_callback_(backend::Callback callback);

    // Generates a new issue info in json format
    void generate_new_issue_info();

    // Update the general <issue_info_> info for the whole system
    void sum_entity_number_issue(int n);
    void add_domain_issue(std::string name);

    bool fill_first_entity_info();

private:

    bool enabled_;

    backend::Listener* listener_;

    models::ListModel* participants_model_;
    models::ListModel* physical_model_;
    models::ListModel* logical_model_;

    models::TreeModel* info_model_;
    models::TreeModel* summary_model_;

    models::TreeModel* issue_model_;
    json issue_info_;

    models::ListModel* source_entity_id_model_;
    models::ListModel* destination_entity_id_model_;

    backend::EntityId last_entity_clicked_;
    backend::EntityKind last_entity_clicked_kind_;

    StatisticsData* statistics_data_;

    backend::SyncBackendConnection backend_connection_;

    // Queue of callbacks from backend to execute in an internal thread
    QRecursiveMutex callback_queue_mutex_;
    QQueue<backend::Callback> callback_queue_;

    QWaitCondition callback_process_cv_;
    std::atomic<bool> callback_process_run_;

    CallbackListener callback_listener_;

    // Thread to
//    class CallbackThread : public QThread
//    {
//        Q_OBJECT
//        void run() override {
//            while(callback_process_run_.load())
//            {
//                callback_process_cv_.w
//            }
//        }
//    signals:
//        void refresh();
//    } callback_thread_;

};

#endif // ENGINE_H
