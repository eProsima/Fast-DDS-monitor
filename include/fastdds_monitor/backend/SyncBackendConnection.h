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
 * @file SyncBackendConnection.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_BACKEND_SYNCBACKENDCONNECTION_H
#define _EPROSIMA_FASTDDS_MONITOR_BACKEND_SYNCBACKENDCONNECTION_H

#include <fastdds_statistics_backend/StatisticsBackend.hpp>
#include <fastdds_statistics_backend/types/types.hpp>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/backend/Listener.h>
#include <fastdds_monitor/model/logical/DomainModelItem.h>
#include <fastdds_monitor/model/logical/TopicModelItem.h>
#include <fastdds_monitor/model/physical/HostModelItem.h>
#include <fastdds_monitor/model/physical/ProcessModelItem.h>
#include <fastdds_monitor/model/physical/UserModelItem.h>
#include <fastdds_monitor/model/SubListedListModel.h>
#include <fastdds_monitor/model/tree/TreeModel.h>


namespace backend {

using namespace models;

/**
 * @brief Class that holds all the backend queries in both sides
 *
 * This class represents the main interconnection point between a backend instance and the main Engine object.
 * In connection with the \c Listener, both classes represents the whole communication between backend and GUI.
 *
 * Even when most of the methods could be static thanks to the Backend Singleton, this class is not singleton
 * or static in order to possible future refactoring to make connections more efficient.
 * i.e. store duplicated queries, manage the connection period, etc.
 */
class SyncBackendConnection
{
public:

    //! Void constructor
    SyncBackendConnection()
    {
    }

    /***********
     * BACKEND *
     **********/

public:

    //! Set the \c PhysicalListener in the backend
    bool set_listener(
            Listener* listener);

    //! Set the \c PhysicalListener in the backend as \c nullptr
    bool unset_listener();

    /**
     * @brief Init a monitor by setting an integer for domain number
     *
     * Calls the Backend \c init_monitor method in order to initialize a new monitor in a new Domain
     *
     * @param domain new domain number
     * @return EntityId of the new Domain Entity created
     */
    EntityId init_monitor(
            int domain);

    /**
     * @brief Init a monitor by setting a string with one or many locators of Discovery Servers
     *
     * Calls the Backend \c init_monitor method in order to initialize a new monitor in a new Domain.
     *
     * The format of the \c locators string would be "ip1:port1,ip2:port2,...,ipN:portN"
     * i.e. "127.0.0.1:11811,127.0.0.1:11812"
     *
     * @param locators string with Discovery Server addresses
     * @return EntityId of the new Domain Entity created
     */
    EntityId init_monitor(
            std::string discovery_server_locators);

    /////
    // Information query functions

    //! Get info from an entity from the Backend
    EntityInfo get_info(
            EntityId id);

    //! Get the id of the topic associated to an endpoint
    backend::EntityId get_endpoint_topic_id(
            backend::EntityId endpoint_id);

    //! Get the id of the domain associated to an entity (Domain, DomainParticipant, Topìc or Endpoints)
    backend::EntityId get_domain_id(
            backend::EntityId entity_id);

    //! Get the \c EntityKind of a given \c EntityId
    EntityKind get_type(
            backend::EntityId id);

    //! Get entity by GUID in string format
    backend::EntityId get_entity_by_guid(
            const std::string& guid);

    //! Get a summary of important data collected from the backend related with the entity with id \c id
    EntityInfo get_summary(
            backend::EntityId id);

    //! Get the name of an entity from the Backend by calling \c get_info
    std::string get_name(
            backend::EntityId id);

    //! Get the alias of an entity from the Backend by calling \c get_info
    std::string get_alias(
            backend::EntityId id);

    //! Get the data type name of an entity from the Backend by calling \c get_info
    std::string get_data_type_name(
            backend::EntityId id);

    //! Get the guid associated to a given entity from the Backend by calling \c get_info
    std::string get_guid(
            backend::EntityId id);

    //! Get the status level of an entity from the Backend by calling \c get_status
    StatusLevel get_status(
            backend::EntityId id);

    //! Get the alive status of an entity from the Backend by calling \c is_active
    bool get_alive(
            backend::EntityId id);

    //! Get the metatraffic attribute of an entity from the Backend by calling \c is_metatraffic
    bool is_metatraffic(
            backend::EntityId id);

    //! Get data from the backend with specific paramenters calling backend \c get_data
    std::vector<backend::StatisticsData> get_data(
            DataKind data_kind,
            EntityId source_entity_id,
            EntityId target_entity_id,
            uint16_t bins = 0,
            StatisticKind statistic_kind = StatisticKind::NONE,
            Timestamp start_time = Timestamp(),
            Timestamp end_time = std::chrono::system_clock::now());

    //! Dump Backend's database to a file
    void dump(
            const std::string file,
            bool clear);

    //! Returns whether data points are available.
    bool data_available(
            DataKind data_kind,
            EntityId source_entity_id,
            EntityId target_entity_id,
            Timestamp start_time = Timestamp(),
            Timestamp end_time = std::chrono::system_clock::now());

    bool get_status_data(
            EntityId source_entity_id,
            ConnectionListSample& sample);

    bool get_status_data(
            EntityId source_entity_id,
            DeadlineMissedSample& sample);

    bool get_status_data(
            EntityId source_entity_id,
            IncompatibleQosSample& sample);

    bool get_status_data(
            EntityId source_entity_id,
            InconsistentTopicSample& sample);

    bool get_status_data(
            EntityId source_entity_id,
            LivelinessChangedSample& sample);

    bool get_status_data(
            EntityId source_entity_id,
            LivelinessLostSample& sample);

    bool get_status_data(
            EntityId source_entity_id,
            ProxySample& sample);

    bool get_status_data(
            EntityId source_entity_id,
            SampleLostSample& sample);

    bool get_status_data(
            EntityId source_entity_id,
            ExtendedIncompatibleQosSample& sample);

    //! Convert a given entity guid to string format
    std::string get_deserialized_guid(
            const backend::GUID_s& data);

    //! Convert a given entity guid in string format to GUID_s
    backend::GUID_s get_serialize_guid(
            const std::string& guid_str);

    //! Get info from an entity from the Backend
    std::vector<EntityId> get_entities(
            EntityKind entity_type,
            EntityId entity_id = EntityId::all());

    //! Get the supported entity kinds of a given data kind
    std::vector<std::pair<EntityKind, EntityKind>> get_data_supported_entity_kinds(
            DataKind data_kind);

    //! Remove all inactive entities from database.
    void clear_entities();

    //! Clear all statistics data of all entities received before a time given.
    void clear_statistics_data(
            Timestamp time_to = the_end_of_time());

    /**********
    * CREATE *
    **********/

    bool entity_exists(
            EntityId entity_id);

protected:

    //! Create a new \c ListItem of class \c Host related with the backend entity with id \c id
    ListItem* create_host_data_(
            backend::EntityId id);

    //! Create a new \c ListItem of class \c User related with the backend entity with id \c id
    ListItem* create_user_data_(
            backend::EntityId id);

    //! Create a new \c ListItem of class \c Process related with the backend entity with id \c id
    ListItem* create_process_data_(
            backend::EntityId id);

    //! Create a new \c ListItem of class \c Domain related with the backend entity with id \c id
    ListItem* create_domain_data_(
            backend::EntityId id);

    //! Create a new \c ListItem of class \c Topic related with the backend entity with id \c id
    ListItem* create_topic_data_(
            backend::EntityId id);

    //! Create a new \c ListItem of class \c Participant related with the backend entity with id \c id
    ListItem* create_participant_data_(
            backend::EntityId id);

    //! Create a new \c ListItem of class \c Endpoint related with the backend entity with id \c id
    ListItem* create_datawriter_data_(
            backend::EntityId id);

    //! Create a new \c ListItem of class \c Endpoint related with the backend entity with id \c id
    ListItem* create_datareader_data_(
            backend::EntityId id);

    //! Create a new \c ListItem of class \c Locator related with the backend entity with id \c id
    ListItem* create_locator_data_(
            backend::EntityId id);

    /************
     * GET DATA *
     ***********/

public:

    /**
     * Updates the entity model used to populate the ComboBox from the list of available entities of a certain type.
     *
     * The form the user fills in to generate a series in a graph has the source and target entities
     * (only for certain data types) on which the data gathering is applied.
     * This function allows to dynamically fill in the model of available entities according to the type of entity
     * selected by the user.
     */
    bool update_get_data_dialog_entity_id(
            models::ListModel* entity_model,
            EntityKind entity_kind,
            bool inactive_visible,
            bool metatraffic_visible);

    //! Give a string with the name of the unit magnitud in which each DataKind is measured
    std::string get_data_kind_units(
            const DataKind data_kind);

    //! Retrive a string vector containing the transport protocols supported by the Statistics Backend Discovery Server.
    std::vector<std::string> ds_supported_transports();

    //! Retrive a string list containing the available statistic kinds.
    std::vector<std::string> get_statistic_kinds();

    //! Retrive a string list containing the available data kinds.
    std::vector<std::string> get_data_kinds();

    //! Returns whether the data kind entered requires a target entity to be defined.
    bool data_kind_has_target(
            const DataKind& data_kind);

    /**
     * Build the source and target vectors of entities given the data kind, the source entity id and the target entity
     * id.
     * Returns whether the data kind requires a target entity.
     */
    bool build_source_target_entities_vectors(
            DataKind data_kind,
            EntityId source_entity_id,
            EntityId target_entity_id,
            std::vector<EntityId>& source_ids,
            std::vector<EntityId>& target_ids);

    //! Request to backend the latest domain view JSON to build the graph
    Graph get_domain_view_graph (
            const EntityId& domain_id);

    //! Retrieve the IDL representation of a topic data type in string format
    std::string get_type_idl (
            const EntityId& entity_id);

protected:

    void change_unit_magnitude(
            std::vector<StatisticsData>& data,
            DataKind data_kind);

    void filter(
            std::vector<StatisticsData>& data,
            DataKind data_kind);

    void sort(
            std::vector<StatisticsData>& data);

    /**************
     * UPDATE ALL *
     *************/

public:

    /**
     * @brief Update the Physical model with every Physical entity in the backend
     *
     * The Physical entities are \c Host \c User and \c Process
     *
     * Gets an already empty/partially/fully filled model.
     * For every entity it already has, it updates its internl information.
     * For every new entity found between the physic entities in the backend, new entities are added to the model.
     * The orphan entities such as User with unknown Host or Process with unknown User are not added or updated.
     *
     * @param physical_model Physical model to update
     * @return true if any change has been made, false otherwise
     */
    bool update_physical_model(
            models::ListModel* physical_model,
            bool inactive_visible,
            bool metatraffic_visible);

    /**
     * @brief Update the Logical model with every Logical entity in the backend
     *
     * The Logical entities are \c Domain \c Topic
     *
     * Gets an already empty/partially/fully filled model.
     * For every entity it already has, it updates its internl information.
     * For every new entity found between the physic entities in the backend, new entities are added to the model.
     * The orphan entities such as Topic with unknown Domain are not added or updated.
     *
     * As Domains are known by \c init_monitor methods, they should not be discovered by this method.
     * Nevertheless, it is in this method when the Domain enters the model.
     *
     * @param logical_model Logical model to update
     * @return true if any change has been made, false otherwise
     */
    bool update_logical_model(
            models::ListModel* logical_model,
            bool inactive_visible,
            bool metatraffic_visible);

    /**
     * @brief Update the DDS model with every DDS entity in the backend
     *
     * The DDS entities are \c Participant \c DataWriter \c DataReader and \c Locator
     *
     * Gets an already empty/partially/fully filled model with only the entities related with the entity  with id \c id
     * For every entity it already has, it updates its internl information.
     * For every new entity found between the physic entities in the backend, new entities are added to the model.
     * The orphan entities such as Endpoints with unknown Participant or Locator without Endpoint
     * are not added or updated.
     *
     * i.e. there exist two Participants below one User (id <u>), but each under different Processes (id <p1> & <p2>),
     * call this method with id <u> and an empty model will fill the model with both Participants and their subentities
     * call this method with id <p1> and an empty model will fill the model with only Participant 1 and its subentities
     * call this method with id <p1> and a model with both participants will update the subentities of Participant 1
     *
     * @warning This method do not affect to those entities that are alredy in the model but are not related with \c id
     *
     * @param dds_model DDS model to update
     * @param id entity to show the DDS entities related to ir
     * @return true if any change has been made, false otherwise
     */
    bool update_dds_model(
            models::ListModel* dds_model,
            EntityId id,
            bool inactive_visible,
            bool metatraffic_visible);

    /////
    // Entity update functions

    /**
     * @brief Update the Host item and their subentities with backend information
     *
     * Regenerate the info of this item from the info in the backend.
     * Iterate over all the physical subentities of this host in the backend.
     * In case the subentity does not exist it creates it.
     * Update every subentity.
     *
     * @param host_item Host item to update
     * @return true if any change has been made, false otherwise
     */
    bool update_host_item(
            ListItem* host_item,
            bool inactive_visible,
            bool metatraffic_visible);

    /**
     * @brief Update the user item and their subentities with backend information
     *
     * Regenerate the info of this item from the info in the backend.
     * Iterate over all the physical subentities of this user in the backend.
     * In case the subentity does not exist it creates it.
     * Update every subentity.
     *
     * @param user_item user item to update
     * @return true if any change has been made, false otherwise
     */
    bool update_user_item(
            ListItem* user_item,
            bool inactive_visible,
            bool metatraffic_visible);

    /**
     * @brief Update the process item with backend information
     *
     * Regenerate the info of this item from the info in the backend
     *
     * @param process_item process item to update
     * @return true if any change has been made, false otherwise
     */
    bool update_process_item(
            ListItem* process_item,
            bool inactive_visible,
            bool metatraffic_visible);

    /**
     * @brief Update the domain item and their subentities with backend information
     *
     * Regenerate the info of this item from the info in the backend.
     * Iterate over all the physical subentities of this domain in the backend.
     * In case the subentity does not exist it creates it.
     * Update every subentity.
     *
     * @param domain_item domain item to update
     * @return true if any change has been made, false otherwise
     */
    bool update_domain_item(
            ListItem* domain_item,
            bool inactive_visible,
            bool metatraffic_visible);

    /**
     * @brief Update the topic item with backend information
     *
     * Regenerate the info of this item from the info in the backend
     *
     * @param topic_item topic item to update
     * @return true if any change has been made, false otherwise
     */
    bool update_topic_item(
            ListItem* topic_item,
            bool inactive_visible,
            bool metatraffic_visible);

    /**
     * @brief Update the participant item and their subentities with backend information
     *
     * Regenerate the info of this item from the info in the backend.
     * Iterate over all the physical subentities of this participant in the backend.
     * In case the subentity does not exist it creates it.
     * Update every subentity.
     *
     * @param participant_item participant item to update
     * @return true if any change has been made, false otherwise
     */
    bool update_participant_item(
            ListItem* participant_item,
            bool inactive_visible,
            bool metatraffic_visible);

    /**
     * @brief Update the datawriter or datareader item and their subentities with backend information
     *
     * Regenerate the info of this item from the info in the backend.
     * Iterate over all the physical subentities of this endpoint in the backend.
     * In case the subentity does not exist it creates it.
     * Update every subentity.
     *
     * @param endpoint_item endpoint item to update
     * @return true if any change has been made, false otherwise
     */
    bool update_endpoint_item(
            ListItem* endpoint_item,
            bool inactive_visible,
            bool metatraffic_visible);

    /**
     * @brief Update the topic item with backend information
     *
     * Regenerate the info of this item from the info in the backend
     *
     * @param topic_item topic item to update
     * @return true if any change has been made, false otherwise
     */
    bool update_locator_item(
            ListItem* locator_item,
            bool inactive_visible,
            bool metatraffic_visible);

protected:

    bool update_item_(
        models::ListItem* item,
        bool (SyncBackendConnection::* update_function)(ListItem*, bool, bool),
        bool inactive_visible,
        bool metatraffic_visible);

    /**
     * General method to encapsulate the common funcionality of updating the info from backend
     * So far it does always return \c true
     */
    bool update_item_info_(
            ListItem* item);

    //! General method to encapsulate the common funcionality of \c update_*_model methods refering to models update
    bool update_model_(
        models::ListModel* model,
        EntityKind type,
        EntityId id,
        bool (SyncBackendConnection::* update_function)(ListItem*, bool, bool),
        models::ListItem* (SyncBackendConnection::* create_function)(EntityId),
        bool inactive_visible,
        bool metatraffic_visible);

    /**************
     * UPDATE ONE *
     *************/

public:

    bool update_host(
            models::ListModel* physical_model,
            EntityId id,
            bool new_entity,
            bool inactive_visible,
            bool metatraffic_visible,
            bool last_clicked);

    bool update_user(
            models::ListModel* physical_model,
            EntityId id,
            bool new_entity,
            bool inactive_visible,
            bool metatraffic_visible,
            bool last_clicked);

    bool update_process(
            models::ListModel* physical_model,
            EntityId id,
            bool new_entity,
            bool inactive_visible,
            bool metatraffic_visible,
            bool last_clicked);

    bool update_domain(
            models::ListModel* logical_model,
            EntityId id,
            bool new_entity,
            bool inactive_visible,
            bool metatraffic_visible,
            bool last_clicked);

    bool update_topic(
            models::ListModel* logical_model,
            EntityId id,
            bool new_entity,
            bool inactive_visible,
            bool metatraffic_visible,
            bool last_clicked);

    bool update_participant(
            models::ListModel* dds_model,
            EntityId id,
            bool new_entity,
            EntityId related_entity_id,
            bool inactive_visible,
            bool metatraffic_visible,
            bool last_clicked);

    bool update_datawriter(
            models::ListModel* dds_model,
            EntityId id,
            bool new_entity,
            bool inactive_visible,
            bool metatraffic_visible,
            bool last_clicked);

    bool update_datareader(
            models::ListModel* dds_model,
            EntityId id,
            bool new_entity,
            bool inactive_visible,
            bool metatraffic_visible,
            bool last_clicked);

    bool update_locator(
            models::ListModel* dds_model,
            EntityId id,
            bool new_entity,
            bool inactive_visible,
            bool metatraffic_visible,
            bool last_clicked);

    //! Set a new alias in backend
    void set_alias(
            const backend::EntityId& id,
            const std::string& new_alias);

protected:

    ListModel* get_model_(
            models::ListModel* parent_model,
            EntityId id,
            EntityKind parent_kind);

    std::vector<ListModel*> get_locator_models_(
            models::ListModel* parent_model,
            EntityId id,
            EntityKind parent_kind);

    bool update_one_entity_in_model_(
        models::ListModel* model,
        EntityId id,
        bool new_entity,
        models::ListItem* (SyncBackendConnection::* create_function)(EntityId),
        bool inactive_visible,
        bool metatraffic_visible,
        bool last_clicked);
};

} //namespace backend

#endif // _EPROSIMA_FASTDDS_MONITOR_BACKEND_SYNCBACKENDCONNECTION_H
