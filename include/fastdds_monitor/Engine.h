// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Monitor.
//
// eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

/**
 * @file Engine.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_ENGINE_H
#define _EPROSIMA_FASTDDS_MONITOR_ENGINE_H

#include <atomic>
#include <tuple>

#include <QQmlApplicationEngine>
#include <QQueue>
#include <QtCharts/QVXYModelMapper>
#include <QThread>
#include <QWaitCondition>
#include <QStringListModel>

#include <fastdds_monitor/backend/Callback.h>
#include <fastdds_monitor/backend/StatusCallback.h>
#include <fastdds_monitor/backend/Listener.h>
#include <fastdds_monitor/backend/SyncBackendConnection.h>
#include <fastdds_monitor/Controller.h>
#include <fastdds_monitor/model/tree/TreeModel.h>
#include <fastdds_monitor/model/info/InfoModel.h>
#include <fastdds_monitor/statistics/dynamic/DynamicStatisticsData.h>
#include <fastdds_monitor/statistics/historic/HistoricStatisticsData.h>
#include <fastdds_monitor/model/tree/StatusTreeModel.h>

struct EntityClicked
{
    backend::EntityId id = backend::ID_ALL;
    backend::EntityKind kind = backend::EntityKind::INVALID;
    bool is_set() const;
    EntityClicked reset();
    EntityClicked set(
            backend::EntityId clicked_entity,
            backend::EntityKind clicked_kind);
};

/**
 * @brief This data struct collects the entities currently clicked and add some logic methods regarding
 * the status of clicked entities.
 * It simplifies Engine by joining a lot of logic that was distributed in many places.
 */
struct EntitiesClicked
{
    enum class EntityKindClicked
    {
        all,
        dds,
        logical_physical
    };

    //! Id of the last Entity clicked or \c ID_ALL
    EntityClicked dds;

    //! Id of the last Entity clicked in physical or logical or \c ID_ALL
    EntityClicked physical_logical;

    bool is_physical_logical_clicked() const;

    bool is_dds_clicked() const;

    std::tuple<
        EntityKindClicked,
        EntityClicked,
        EntityClicked>
    click(
            backend::EntityId clicked_entity,
            backend::EntityKind clicked_kind);

    std::pair<EntityClicked, EntityClicked> unclick();

    EntityClicked unclick_dds();
};

/**
 * Main class that connects the View (QML), the models (Controller) and the backend (Listener + SyncBackendConnection)
 *
 * It holds the different models that are used to represent data in the view:
 *  - Physical model    : items representing hosts, users and processes
 *  - Logical model     : items representing domains and topics
 *  - DDS model         : items representing participants, endpoints and locators
 *  - Info model        : contains the info of the entity clicked
 *  - Summary model     : contains the statistic summary info from the entity clicked
 *  - Issue model       : contains info about events: callbacks, issues and number of entities discovered
 *  - source ent model  : TODO
 *  - dest entity model : TODO
 *  - StatisticsData    : handles the historic series
 *  - DynamicData       : handles the dynamic series
 * These models are used to represent data in the view.
 * The \c Controller object interact between the user interface and the Engine, translating the user actions.
 *
 * There are two different interactions between the Engine and the backend: Syncronous and Asyncronous.
 *
 * The Async connection remains in data that arrives from the backend.
 * It is hold by the \c Listener that communicates the Engine via signals when any callback arrives.
 *
 * The Sync connection remains in \c SyncBackendConnection object.
 * The Engine uses this object any time it needs to get data from the backend due a user evert or a async event.
 */
class Engine : public QQmlApplicationEngine
{
    Q_OBJECT

public:

    //! Standard void constructor
    Engine();

    //! Release listener and all models
    ~Engine();

    /**
     * @brief Start the Engine execution
     *
     * Create and connect backend \c Listener .
     * Create and fill models.
     * Register models in QML.
     *
     * @return Engine pointer
     */
    QObject* enable();

    /**
     * @brief Initialize a monitor in a domain by number
     * @param domain number of the domain
     * @param easy_mode_ip IP address of the remote discovery server used in ROS2 Easy Mode.
     */
    void init_monitor(
            int domain,
            std::string easy_mode_ip = "");

    /**
     * @brief Initialize a monitor in a domain by discovery server locators
     * @param domain number of the domain
     */
    void init_monitor(
            QString discovery_server_locators);

    /////
    // PHYSICAL PARTITION

    /**
     * @brief Update the internal physical model with a host notification
     * @param id host id to create or update
     * @return true if any change in model has been done
     */
    bool update_host(
            const backend::EntityId& id,
            bool new_entity = true,
            bool last_clicked = false);

    /**
     * @brief Update the internal physical model with a user notification
     * @param id user id to create or update
     * @return true if any change in model has been done
     */
    bool update_user(
            const backend::EntityId& id,
            bool new_entity = true,
            bool last_clicked = false);

    /**
     * @brief Update the internal physical model with a process notification
     * @param id process id to create or update
     * @return true if any change in model has been done
     */
    bool update_process(
            const backend::EntityId& id,
            bool new_entity = true,
            bool last_clicked = false);

    /////
    // LOGICAL PARTITION

    /**
     * @brief Update the internal logical model with a domain notification
     * @param id domain id to create or update
     * @return true if any change in model has been done
     */
    bool update_domain(
            const backend::EntityId& id,
            bool new_entity = true,
            bool last_clicked = false);

    /**
     * @brief Update the internal logical model with a topic notification
     * @param id topic id to create or update
     * @return true if any change in model has been done
     */
    bool update_topic(
            const backend::EntityId& id,
            bool new_entity = true,
            bool last_clicked = false);

    /////
    // DDS PARTITION

    /**
     * @brief Update the internal dds model with a participant notification
     *
     * It is possible that this entity is not being showed because of the entity clicked
     * an so that this function do not update the model.
     *
     * @param id participant id to create or update
     * @return true if any change in model has been done
     */
    bool update_participant(
            const backend::EntityId& id,
            bool new_entity = true,
            bool last_clicked = false);

    /**
     * @brief Update the internal dds model with a datawriter notification
     *
     * It is possible that this entity is not being showed because of the entity clicked
     * an so that this function do not update the model.
     *
     * @param id datawriter id to create or update
     * @return true if any change in model has been done
     */
    bool update_datawriter(
            const backend::EntityId& id,
            bool new_entity = true,
            bool last_clicked = false);

    /**
     * @brief Update the internal dds model with a datareader notification
     *
     * It is possible that this entity is not being showed because of the entity clicked
     * an so that this function do not update the model.
     *
     * @param id datareader id to create or update
     * @return true if any change in model has been done
     */
    bool update_datareader(
            const backend::EntityId& id,
            bool new_entity = true,
            bool last_clicked = false);

    /**
     * @brief Update the internal dds model with a locator notification
     *
     * It is possible that this entity is not being showed because of the entity clicked
     * an so that this function do not update the model
     *
     * @param id locator id to create or update
     * @return true if any change in model has been done
     */
    bool update_locator(
            const backend::EntityId& id,
            bool new_entity = true,
            bool last_clicked = false);

    /**
     * @brief Update the entity status model with the status kind received
     *
     * @param id entity id
     * @param kind StatusKind reported
     * @return true if any change in model has been done
     */
    bool update_entity_status(
            const backend::EntityId& id,
            backend::StatusKind kind);

    /**
     * @brief Update the entity status counters and populate the model with empty message if empty
     *
     * @param id entity id
     * @return false
     */
    bool remove_inactive_entities_from_status_model(
            const backend::EntityId& id);

    /**
     * @brief Update the internal dds model with entities related with Entity referenced by \c id
     *
     * The backend allows to ask for all the related entities to an Entity given.
     * In this case, the Engine ask the backend for all participants related with the entity given, and
     * create a model with those participants and all their subentities.
     *
     * If called with \c ID_ALL all participants are used to fill the model
     *
     * @param id Entity id of the entity the model must reference
     * @return true if any change in model has been done
     */
    bool update_dds_data(
            const backend::EntityId& id);

    //! Clear all internal models
    void reset_all_data();
    //! Clear the internal dds model
    void reset_dds_data();
    //! Clear the internal logic model
    void reset_logic_data();
    //! Clear the internal physical model
    void reset_physical_data();

    /////
    // ON CLICKED

    /**
     * @brief Call the event chain when an entity is clicked
     *
     * For every entity it updates the info model and the summary model to reference this entity clicked.
     * If the entity is of physical or logical kind, it updates the dds model as well with only the participants that
     * are related with this entity.
     *
     * @param id Entity id of the entity clicked
     * @param kind Entity kind of the entity clicked
     * @param update_dds Update the dds model
     * @param reset_dds Reset the dds model before update it
     * @return true if any change in any model has been done
     */
    bool entity_clicked(
            backend::EntityId id,
            backend::EntityKind kind,
            bool update_dds = true,
            bool reset_dds = true);

    //! TODO
    bool on_selected_entity_kind(
            backend::EntityKind entity_kind,
            QString entity_model_id);

    /**
     * @brief Add a static series in when user set new series parameters
     *
     * Calls get_data with the params given and appends the new series to \c statistics_data_ (historic data)
     */
    QtCharts::QVXYModelMapper* on_add_statistics_data_series(
            quint64 chartbox_id,
            backend::DataKind data_kind,
            backend::EntityId source_entity_id,
            backend::EntityId target_entity_id,
            quint16 bins,
            quint64 start_time,
            bool start_time_default,
            quint64 end_time,
            bool end_time_default,
            backend::StatisticKind statistic_kind);

    /**
     * @brief add a callback arrived from the backend to the callback queue
     *
     * Add a callback to the callback queue in order to process it afterwards by the main thread.
     * Emit a signal that communicate the main thread that there are info to process in the callback queue.
     * Add a callback issue.
     *
     * @param callback new callback to add
     * @return true
     */
    bool add_callback(
            backend::Callback callback);

    /**
     * @brief add a status callback arrived from the backend to the status callback queue
     *
     * Add a status callback to the status callback queue in order to process it afterwards by the main thread.
     * Emit a signal that communicate the main thread that there are info to process in the status callback queue.
     * Add a status callback issue.
     *
     * @param callback new status callback to add
     * @return true
     */
    bool add_callback(
            backend::StatusCallback callback);

    /**
     * @brief Refresh the view
     *
     * Erase the last entity clicked, and set it as \c ID_ALL so the info shown does nor reference any single entity.
     * Refresh all the models with the new configuration.
     * Erase the callback issue list.
     *
     * @param maintain_clicked whether the entities currently clicked must be maintained (in case still exist)
     * after the refresh and refill of every model.
     */
    void refresh_engine(
            bool maintain_clicked = false);

    /**
     * @brief Erase the inactive entities from database.
     */
    void clear_entities();

    /**
     * @brief Clear all statistics data of all entities received before a time given.
     */
    void clear_statistics_data(
            quint64 time_to = 0);

    /**
     * @brief Erase the callback log list
     */
    void clear_log();

    /**
     * @brief Erase the issues list
     */
    void clear_issues();

    /**
     * @brief Pop callbacks from the callback queues while non empty and update the models
     *
     * @warning This method must be executed from the main Thread (or at least a QThread) so the models are
     * updated in the view when modified.
     */
    void process_callback_queue();

    /**
     * @brief Pop status callbacks from the status callback queues while non empty and update the models
     *
     * @warning This method must be executed from the main Thread (or at least a QThread) so the models are
     * updated in the view when modified.
     */
    void process_status_callback_queue();

    //! Refresh summary panel
    void refresh_summary();

    //! Process a new error showing a Error Dialog in screen and add it to issues model
    void process_error(
            std::string error_msg,
            ErrorType error_type = ErrorType::GENERIC);

    /**
     * @brief Add a new data point in an internal dynamic chartbox
     *
     * It gets the parameters needed to call \c get_data from \c DynamicData and its internal chartbox referenced by
     * \c chartbox_id .
     * It calls \c get_data to get 1 value for each series inside the chartbox, and the update the chartbox
     *
     * @param chatbox_id unique id of the chartbox inside the \c DynamicData object
     * @param time_to new time reference to now
     */
    void update_dynamic_chartbox(
            quint64 chartbox_id,
            quint64 time_to);

    //! Change alias to an already existing entity and refresh its info
    void set_alias(
            const backend::EntityId& entity_id,
            const std::string& new_alias,
            const backend::EntityKind& entity_kind);

    /**
     * This methods updates the info and summary if the entity clicked (the entity that is being shown) is the
     * entity updated.
     */
    bool update_entity(
        const backend::EntityId& entity_updated,
        bool (Engine::* update_function)(const backend::EntityId&, bool, bool),
        bool new_entity = true,
        bool last_clicked = false);

    //! Change inactive visible parameter
    void change_inactive_visible();

    //! Change metatraffic visible parameter
    void change_metatraffic_visible();

    //! Change ros2 demangling active status
    void change_ros2_demangling();

    //! Get if inactive entities must be visible
    bool inactive_visible() const;

    //! Get if metatraffic must be visible
    bool metatraffic_visible() const;

    //! Get if ROS 2 demangling is active
    bool ros2_demangling_active() const;

    //! Give a string with the name of the unit magnitud in which each DataKind is measured
    std::string get_data_kind_units(
            const QString& data_kind);

    /**
     * @brief Export the series given to a new csv file
     *
     * Export one or multiple series to a new csv file.
     * Each series to export is given in a vector as chartobox id and series index to get the data from the models.
     * Each series to export is given with its headers in order to save them in the csv and can import the file.
     *
     * @param file_name         path and name to the new csv file
     * @param chartbox_ids      ids of the chartboxes of each series
     * @param series_indexes    indexes of the series inside each chartbox
     * @param data_kinds        DataKind that refers to the each series
     * @param chartbox_names    Title of the chartbox this series belongs
     * @param label_names       Label of each series
     */
    void save_csv(
            const QString& file_name,
            const QList<quint64>& chartbox_ids,
            const QList<quint64>& series_indexes,
            const QStringList& data_kinds,
            const QStringList& chartbox_names,
            const QStringList& label_names);

    /**
     * @brief Dump Fast DDS Statistics Backend's database to a file.
     *
     * @param file_name The name of the file where the database is dumped.
     * @param clear If true, clear all the statistics data of all entities.
     */
    void dump(
            const QString& file_name,
            bool clear);

    //! Retrive a string vector containing the transport protocols supported by the Statistics Backend Discovery Server.
    std::vector<std::string> ds_supported_transports();

    //! Retrive a string list containing the available statistic kinds.
    std::vector<std::string> get_statistic_kinds();

    //! Retrive a string list containing the available data kinds.
    std::vector<std::string> get_data_kinds();

    //! Retrieve the name associated to a specific entity
    std::string get_name(
            const backend::EntityId& entity_id);

    //! Retrieve the data type name associated to a specific entity
    std::string get_data_type_name(
            const backend::EntityId& entity_id);

    //! Retrieve the IDL representation associated to a specific data type
    std::string get_type_idl(
            const backend::EntityId& entity_id);

    //! Retrieve the original IDL representation associated to a specific data type, if demangled from ROS 2 (regular IDL otherwise)
    std::string get_ros2_type_idl(
            const backend::EntityId& entity_id);

    //! Retrieve the demangled IDL name associated to a specific data type, if demangled from ROS 2 (regular name otherwise)
    std::string get_ros2_type_name(
            const backend::EntityId& entity_id);

    //! Retrieve the topic id associated to a specific endpoint
    models::EntityId get_endpoint_topic_id(
            const models::EntityId& endpoint_id);

    //! Retrieve the id of the domain associated to an entity (Domain, DomainParticipant, Topìc or Endpoints)
    models::EntityId get_domain_id(
            const models::EntityId& entity_id);

    //! Returns whether the data kind entered requires a target entity to be defined.
    bool data_kind_has_target(
            const QString& data_kind);

    //! Change the max number of points allowed in a specific DataModel
    void change_max_points(
            quint64 chartbox_id,
            quint64 series_id,
            quint64 new_max_point);

    //! Request to backend the latest domain view JSON to build the graph
    backend::Graph get_domain_view_graph (
            const backend::EntityId& domain_id);

    //! Load an XML file containing DDS profiles
    bool load_xml_profiles_file(
            const QString& file_path);

    //! Initialize a monitor using a profile name
    void init_monitor_with_profile(
            const QString& profile_name);

signals:

    /**
     * Internal signal that communicate that there are callbacks to process by the main Thread.
     * Arise from \c add_callback
     */
    void new_callback_signal();

    /**
     * Internal signal that communicate that there are status callbacks to process by the main Thread.
     * Arise from \c add_callback
     */
    void new_status_callback_signal();

public slots:

    /**
     * Receive the internal signal \c new_callback_signal and start the process of callback
     * queue by \c process_callback_queue
     */
    void new_callback_slot();

    /**
     * Receive the internal signal \c new_status_callback_signal and start the process of status
     * callback queue by \c process_status_callback_queue
     */
    void new_status_callback_slot();

protected:

    /**
     * @brief Clear and fill the Info Model by the info from the backend of the entity \c id
     *
     * In case \c id is \c ID_ALL (possible at the begininning of an execution or after refresh)
     * the info shown is a message that no entity is being clicked.
     *
     * @todo this method could update the model by the info stored in an item and not calling the backend
     * to receive data it already has.
     * However, this requires to find the entity in the models and could be less efficient than ask the backend.
     *
     * @param id id of the entity to get the info
     * @return true if any change in any model has been done
     */
    bool fill_entity_info_(
            backend::EntityId id = backend::ID_ALL);

    /**
     * Update the info model with an initial message that says there are no monitors active.
     * This method is called instead of \c fill_entity_info_ at the beginning of the execution.
     */
    bool fill_first_entity_info_();


    /**
     * @brief Clear and fill the Sumary Model by the info from the backend of the entity \c id
     *
     * @param id id of the entity to get the info
     * @return true if any change in any model has been done
     */
    bool fill_summary_(
            backend::EntityId id = backend::ID_ALL);

    /**
     * @brief Clear and fill the Issue Model
     *
     * @return true if any change in any model has been done
     */
    bool fill_issue_();

    /**
     * @brief Clear and fill the Log Model
     *
     * @return true if any change in any model has been done
     */
    bool fill_log_();

    /**
     * @brief Clear and fill the Status Model
     *
     * @return true if any change in any model has been done
     */
    bool fill_status_();

    //! Add a new callback message to the Log model
    bool add_log_callback_(
            std::string callback,
            std::string time);

    //! Add a new issue message to the Issue model
    bool add_issue_info_(
            std::string issue,
            std::string time);

    //! Add a new callback message to the Status model
    bool add_status_domain_(
            std::string name,
            std::string time);

    /**
     * Generates a new issue info model from the main schema
     * The Issue model schema has:
     * - "Issues" tag - to collect issues messages
     */
    void generate_new_issue_info_();

    /**
     * Generates a new log info model from the main schema
     * The Issue model schema has:
     * - "Callbacks" tag - to collect callbacks messages
     */
    void generate_new_log_info_();

    /**
     * Generates a new status info model from the main schema
     * The Issue model schema has:
     * - "Entities" tag that has:
     *   - "Domains" tag - to collect domains initialized
     *   - "Entities" tag - to show the number of entities discovered
     */
    void generate_new_status_info_();

    //! Update the issue model "Entities" count adding \c n
    void sum_entity_number_issue(
            int n);

    //! Update the whole physical model
    bool fill_physical_data_();

    //! Update the whole logical model
    bool fill_logical_data_();

    //! Update the whole dds model
    bool fill_dds_data_();

    //! TODO
    bool fill_available_entity_id_list_(
            backend::EntityKind entity_kind,
            QString entity_model_id);

    //! Common behaviour for both \c init_monitor functions
    void shared_init_monitor_(
            backend::EntityId domain_id);

    //! True if there are callbacks in the callback queue
    bool are_callbacks_to_process_();

    //! True if there are status callbacks in the callback queue
    bool are_status_callbacks_to_process_();

    //! Pop a callback from callback queues and call \c read_callback for that callback
    bool process_callback_();

    //! Pop a status callback from callback queues and call \c read_callback for that status callback
    bool process_status_callback_();

    //! Update the model concerned by the entity in the callback
    bool read_callback_(
            backend::Callback callback);

    //! Update the model concerned by the entity in the status callback
    bool read_callback_(
            backend::StatusCallback callback);

    //! Common method to demultiplex to update functions depending on the entity kind
    bool update_entity_generic(
            backend::EntityId entity_id,
            backend::EntityKind entity_kind,
            bool is_update = false,
            bool is_last_clicked = false);

    //! Remove all the callbacks from issue model (called in \c refresh )
    void clear_callback_log_();

    //! Clear issues panel information
    void clear_issue_info_();

    /////
    // Variables

    //! Set to true if the engine is being enabled
    bool enabled_;

    //! Reference to the \c Listener that is being set to the backend as callback communicator
    backend::Listener* listener_;

    //! Data Model for DDS entities (Participant, Endpoint, Locator)
    models::ListModel* participants_model_;

    //! Data Model for Physical entities (Host, User, Process)
    models::ListModel* physical_model_;

    //! Data Model for Logical entities (Domain, Topic)
    models::ListModel* logical_model_;

    //! Data Model for Info of the clicked entity
    models::InfoModel* info_model_;

    //! Data Model for Summary of the clicked entity
    models::TreeModel* summary_model_;

    //! Data Model for Issue. Collects general messages and info from the whole system
    models::TreeModel* issue_model_;

    //! Data that is represented in the Issue Model when this model is refreshed
    backend::Info issue_info_;

    //! Data Model for Log. Collects logging messages from application execution
    models::TreeModel* log_model_;

    //! Data that is represented in the Log Model when this model is refreshed
    backend::Info log_info_;

    //! Data Model for Fast DDS Monitor status. Collects the total amount of entities discovered by the monitor
    models::TreeModel* status_model_;

    //! Data that is represented in the Status Model when this model is refreshed
    backend::Info status_info_;

    //! Data Model for Fast DDS Monitor status view. Collects all entities statuses detected by the monitor service
    models::StatusTreeModel* entity_status_model_;

    //! Display and allow to filter Model for Fast DDS Monitor status view.
    models::StatusTreeModel* entity_status_proxy_model_;

    //! TODO
    models::ListModel* source_entity_id_model_;

    //! TODO
    models::ListModel* destination_entity_id_model_;

    //! Ids of the last Entity clicked
    EntitiesClicked last_entities_clicked_;

    //! QML connected object to handler the static series created
    HistoricStatisticsData* historic_statistics_data_;

    /**
     * @brief QML connected object to handler the dynamic series created
     *
     * It handles several \c DynamicChartBox (as many as chartbox in real time the user has created)
     * and connect all the QML calls for user active to them (create/delete series,
     * create/delete chartboxes, get data to update/new data series data, etc.)
     */
    DynamicStatisticsData* dynamic_statistics_data_;

    //! Object that manage all the communications with the backend
    backend::SyncBackendConnection backend_connection_;

    //! Mutex to protect \c callback_queue_
    std::recursive_mutex callback_queue_mutex_;

    //! Mutex to protect \c status_callback_queue_
    std::recursive_mutex status_callback_queue_mutex_;

    //! Queue of Callbacks that have arrived by the \c Listener and have not been processed
    QQueue<backend::Callback> callback_queue_;

    //! Queue of status Callbacks that have arrived by the \c Listener and have not been processed
    QQueue<backend::StatusCallback> status_callback_queue_;

    //! Object that manage all the communications with the QML view
    Controller* controller_;

    //! Time when the monitor has been started. It will be used as default timestamp
    backend::Timestamp initial_time_;

    //! Whether the inactive entities must be visible in the model
    bool inactive_visible_;

    //! Whether metatraffic must be visible in the model
    bool metatraffic_visible_;

    //! Whether the ROS 2 demangling is active
    bool ros2_demangling_active_;

    /**
     * Protect the dds model while a new monitor is being created
     *
     * This mutex is needed because when a new Domain is initialized, it is set as entity:clicked.
     * Thus, the dds model is filled, and so clear and check in database to create it from scratch.
     * If during this process the callbacks of the entities of this new domain arrive (and it is very likely
     * to happen) there are going to create entities already created.
     */
    std::recursive_mutex initializing_monitor_;

    //! All status log
    backend::Info status_status_log_;

    QStringListModel* participant_xml_profiles_;
};

#endif // _EPROSIMA_FASTDDS_MONITOR_ENGINE_H
