// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file Engine.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_ENGINE_H
#define _EPROSIMA_FASTDDS_MONITOR_ENGINE_H

#include <atomic>

#include <QQmlApplicationEngine>
#include <QQueue>
#include <QThread>
#include <QWaitCondition>

#include <fastdds_monitor/backend/Callback.h>
#include <fastdds_monitor/backend/Listener.h>
#include <fastdds_monitor/backend/Listener.h>
#include <fastdds_monitor/backend/SyncBackendConnection.h>
#include <fastdds_monitor/Controller.h>
#include <fastdds_monitor/model/tree/TreeModel.h>
#include <fastdds_monitor/statistics/dynamic/DynamicStatisticsData.h>
#include <fastdds_monitor/statistics/historic/HistoricStatisticsData.h>

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
     */
    void init_monitor(
            int domain);

    /**
     * @brief Initialize a monitor in a domain by discovery server locators
     * @param domain number of the domain
     */
    void init_monitor(
            QString locators);

    /////
    // PHYSICAL PARTITION

    /**
     * @brief Update the internal physical model with a host notification
     * @param id host id to create or update
     * @return true if any change in model has been done
     */
    bool update_host(
            const backend::EntityId& id,
            bool new_entity = true);

    /**
     * @brief Update the internal physical model with a user notification
     * @param id user id to create or update
     * @return true if any change in model has been done
     */
    bool update_user(
            const backend::EntityId& id,
            bool new_entity = true);

    /**
     * @brief Update the internal physical model with a process notification
     * @param id process id to create or update
     * @return true if any change in model has been done
     */
    bool update_process(
            const backend::EntityId& id,
            bool new_entity = true);

    /////
    // LOGICAL PARTITION

    /**
     * @brief Update the internal logical model with a domain notification
     * @param id domain id to create or update
     * @return true if any change in model has been done
     */
    bool update_domain(
            const backend::EntityId& id,
            bool new_entity = true);

    /**
     * @brief Update the internal logical model with a topic notification
     * @param id topic id to create or update
     * @return true if any change in model has been done
     */
    bool update_topic(
            const backend::EntityId& id,
            bool new_entity = true);

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
            bool new_entity = true);

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
            bool new_entity = true);

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
            bool new_entity = true);

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
            bool new_entity = true);

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

    /**
     * @brief Clear the internal dds model
     */
    void reset_dds_data();

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
     * @param update_dds Reset the dds model before update it
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
    bool on_add_statistics_data_series(
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
     * @brief Refresh the view
     *
     * Erase the last entity clicked, and set it as \c ID_ALL so the info shown does nor reference any single entity.
     * Refresh all the models with the new configuration.
     * Erase the callback issue list.
     */
    void refresh_engine();

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
        bool (Engine::* update_function)(const backend::EntityId&, bool),
        bool new_entity = true);

    //! Change inactive visible parameter
    void change_inactive_visible();

    //! Get if inactive entities must be visible
    bool inactive_visible() const;

signals:

    /**
     * Internal signal that communicate that there are callbacks to process by the main Thread.
     * Arise from \c add_callback
     */
    void new_callback_signal();

public slots:

    /**
     * Receive the internal signal \c new_callback_signal and start the process of
     * callback queue by \c process_callback_queue
     */
    void new_callback_slot();

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

    //! Pop a callback from callback queues and call \c read_callback for that callback
    bool process_callback_();

    //! Update the model concerned by the entity in the callback
    bool read_callback_(
            backend::Callback callback);

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
    models::TreeModel* info_model_;

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

    //! TODO
    models::ListModel* source_entity_id_model_;

    //! TODO
    models::ListModel* destination_entity_id_model_;

    //! Id of the last Entity clicked or \c ID_ALL
    backend::EntityId last_entity_clicked_;

    //! Kind of the last Entity clicked or \c INVALID
    backend::EntityKind last_entity_clicked_kind_;

    //! Id of the last Entity clicked in physical or logical or \c ID_ALL
    backend::EntityId last_physical_logical_entity_clicked_;

    //! Kind of the last Entity clicked in physical or logical or \c INVALID
    backend::EntityKind last_physical_logical_entity_clicked_kind_;

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

    //! Queue of Callbacks that have arrived by the \c Listener and have not been processed
    QQueue<backend::Callback> callback_queue_;

    //! Object that manage all the communications with the QML view
    Controller* controller_;

    //! Time when the monitor has been started. It will be used as default timestamp
    backend::Timestamp initial_time_;

    //! Whether the inactive entities must be visible in the model
    bool inactive_visible_;

    /**
     * Protect the dds model while a new monitor is being created
     *
     * This mutex is needed because when a new Domain is initialie, it is set as entity:clicked.
     * Thus, the dds model is filled, and so clear and check in database to create it from scratch.
     * If during this process the callbacks of the entities of this new domain arrive (and it is very likely
     * to happen) there are going to create entities already created.
     */
    std::recursive_mutex initializing_monitor_;
};

#endif // _EPROSIMA_FASTDDS_MONITOR_ENGINE_H
