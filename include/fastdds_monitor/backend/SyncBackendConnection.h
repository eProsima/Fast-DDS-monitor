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
 * @file SyncBackendConnection.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_BACKEND_SYNCBACKENDCONNECTION_H
#define _EPROSIMA_FASTDDS_MONITOR_BACKEND_SYNCBACKENDCONNECTION_H

#include <fastdds_statistics_backend/StatisticsBackend.hpp>

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

    /////
    // Listener functions

    //! Set the \c PhysicalListener in the backend
    bool set_listener(
            Listener* listener);

    //! Set the \c PhysicalListener in the backend as \c nullptr
    bool unset_listener();

    /////
    // Model update functions

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
            models::ListModel* physical_model);

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
            models::ListModel* logical_model);

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
            EntityId id);

    // TODO
    bool update_get_data_dialog_entity_id(
            models::ListModel* entity_model,
            EntityKind entity_kind);

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
            ListItem* host_item);

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
            ListItem* user_item);

    /**
     * @brief Update the process item with backend information
     *
     * Regenerate the info of this item from the info in the backend
     *
     * @param process_item process item to update
     * @return true if any change has been made, false otherwise
     */
    bool update_process_item(
            ListItem* process_item);

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
            ListItem* domain_item);

    /**
     * @brief Update the topic item with backend information
     *
     * Regenerate the info of this item from the info in the backend
     *
     * @param topic_item topic item to update
     * @return true if any change has been made, false otherwise
     */
    bool update_topic_item(
            ListItem* topic_item);

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
            ListItem* participant_item);

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
            ListItem* endpoint_item);

    /**
     * @brief Update the topic item with backend information
     *
     * Regenerate the info of this item from the info in the backend
     *
     * @param topic_item topic item to update
     * @return true if any change has been made, false otherwise
     */
    bool update_locator_item(
            ListItem* locator_item);

    /////
    // Monitor manage functions

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
            QString locators);

    /////
    // Information query functions

    //! Get info from an entity from the Backend
    EntityInfo get_info(
            EntityId id);

    //! Get the \c EntityKind of a given \c EntityId
    EntityKind get_type(
            backend::EntityId id);

    //! Get a summary of important data collected from the backend related with the entity with id \c id
    EntityInfo get_summary(
            backend::EntityId id);

    //! Get the name of an entity from the Backend by calling \c get_info
    std::string get_name(
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

    //! Get info from an entity from the Backend
    std::vector<EntityId> get_entities(
            EntityKind entity_type,
            EntityId entity_id = EntityId::all());

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

    /**
     * General method to encapsulate the common funcionality of updating the info from backend
     * So far it does always return \c true
     */
    bool update_item_info_(
            ListItem* item);

    //! General method to encapsulate the common funcionality of \c update_*_item methods refereing to items update
    bool update_subitems_(
        SubListedListItem * item,
        backend::EntityKind type,
        bool (SyncBackendConnection::* update_function)(ListItem*),
        ListItem * (SyncBackendConnection::* create_function)(backend::EntityId));

    //! General method to encapsulate the common funcionality of \c update_*_model methods refering to models update
    bool update_model_(
        ListModel * model,
        EntityKind type,
        EntityId id,
        bool (SyncBackendConnection::* update_function)(ListItem*),
        ListItem * (SyncBackendConnection::* create_function)(EntityId));

};

} //namespace backend

#endif // _EPROSIMA_FASTDDS_MONITOR_BACKEND_SYNCBACKENDCONNECTION_H
