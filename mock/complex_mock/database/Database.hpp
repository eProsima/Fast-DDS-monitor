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
 * @file Database.hpp
 */

#include <atomic>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <tuple>

#include <fastdds_statistics_backend/listener/PhysicalListener.hpp>
#include <fastdds_statistics_backend/types/types.hpp>

#include "../entities/headers/Entity.hpp"

#ifndef _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_ENTITYCOLLECTOR_HPP_
#define _EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_ENTITYCOLLECTOR_HPP_

namespace eprosima {
namespace statistics_backend {

#define DATA_GENERATION_TIME 15
#define MIN_DATA_GENERATION_TIME 3

/**
 * Singleton Class that store the Entities, and has an API to access the information of each of them.
 * Store and manage the Listener and the thread to callback information.
 * Manage the thread related with new data generation.
 */
class Database
{
public:

    /**
     * @brief Return the Singleton instance of Database
     *
     * @return Database Singleton pointer
     */
    static Database* get_instance()
    {
        static Database instance;
        return &instance;
    }

    /**
     * @brief Listener setter
     *
     * @param listener new listener
     */
    void listener(
            PhysicalListener* listener);

    /**
     * @brief Add a new random domain and random entities underneath
     *
     * @return Entity Id of the new Domain Entity
     */
    EntityId add_domain();

    /**
     * @brief Return the ids related with an entity of one kind
     *
     * It simulates the method \c get_entities in the Statistics Backend.
     * In case the id is ALL, it returns all the entities of one kind.
     * Otherwise, it searchs in a graph and returns all the entities of kind \c entity_type related with this id.
     *
     * @param entity_type kind of the entity that is been looking for
     * @param entity_id id of the entity that return entities must be related. ID ALL to get all entities of one kind
     *
     * @return Vector of ids of entities that match the query
     */
    std::vector<EntityId> get_entities(
            EntityKind entity_type,
            EntityId entity_id);

    /**
     * @brief Get the information of an entity
     *
     * Informtion in json format is retieved for the entity with the id \c entity_id .
     * This information always retrieves the tag "name" and the tag "id"
     *
     * @param entity_id id of the entity to retrieve the info
     *
     * @return Indo in json format
     */
    Info get_info(
            EntityId entity_id);

    /**
     * @brief Return a map of all entities
     *
     * @return Map with key ID and value pointer to an entity
     */
    std::map<EntityId, EntityPointer>& get_all_entities();

    /**
     * @brief Notify the condition variables to start the working threads
     */
    void start();

    /**
     * @brief Notify the condition variables to stop the working threads
     *
     * @warning Once stop is called, the threads stop and they do not start again
     */
    void stop();

    /**
     * @brief Retrieve a new ID not used yet in the Database
     */
    int64_t next_id();

    /**
     * @brief Return the entity related with the id
     *
     * @param id id to the entity
     *
     * @return pointer to the entity if exists
     */
    EntityPointer get_entity(
            EntityId id);

    /**
     * @brief Retrieve the number of domains initialized till this moment
     */
    size_t count_domains();

    //! Change entity name
    void set_alias(
            EntityId id,
            std::string new_alias);

    //! Get active status from an entity. Default true.
    bool get_active(
            EntityId id);

protected:

    /**
     * Default constructor (only called by singleton).
     * It starts the threads
     */
    Database();

    /**
     * Default constructor.
     * It calls \c stop method and join the threads
     */
    ~Database();

    /**
     * Generates random entities over time.
     * It starts by condition variable notification and sleep for a time depending the number of domains.
     * Each time it wakes, it creates new entities in a domain that is rotating (one domain each time).
     * It keeps running while \c run_ is active and when it is not, it wakes instantly by notification and closes.
     */
    void generate_random_entity_thread_();

    /**
     * Send callbacks through the listener when new entities are added.
     * It starts to run by condition varible notification, and wakes up every time there are callbacks to send.
     * It keeps running while \c run_ is active, and sleep while there are no new callbacks.
     */
    void callback_listener_thread_();

    //! Add a new entity in the Database, store a callback for the thread to send it and notify the thread
    void add_entity_(
            EntityPointer entity,
            EntityId domain);

    //! Add new entities by calling add_entity one by one
    void add_entities_(
            std::vector<EntityPointer> entities,
            EntityId domain);

    //! Return the number of entities stored
    size_t count_entities_();

private:

    //! Contain the \c EntityId of every domain initialized
    std::vector<EntityId> domains_;

    //! Store all the entities by key \c EntityId and value \c EntityPointer to the entity
    std::map<EntityId, EntityPointer> entities_;

    /**
     * Store the callbacks that will be sent by the callback thread.
     * Each tuple is formed by: < New element Id , Kind , Domain Id >
     */
    std::vector<std::tuple<EntityId, EntityKind, EntityId>> new_entities_;

    //! Last \c id used by the \c Database
    int64_t last_id_;

    //! Physical Listener stored by the application
    PhysicalListener* listener_;

    /////
    // Thread mutex and variables

    //! Mutex to protect the entities structures
    mutable std::recursive_mutex data_mutex_;

    //! Indicates to the threads that must start. It is set in \c start
    std::atomic<bool> start_;
    //! Indicates to the threads that must keep running. It is deactivated in \c stop
    std::atomic<bool> run_;

    /////
    // Data Generation Thread

    //! Thread that generates random entities with a period depending on the number of domains
    std::thread generate_entity_thread_;

    /**
     * It notifies to Data Generator thread that must start.
     * It is also used to wake the thread during a sleep to stop it.
     */
    mutable std::condition_variable cv_run_;
    //! Mutex asociated to \c cv_run_
    mutable std::mutex run_mutex_;

    /////
    // Callback Thread

    // Condition variable to call callbacks from listener.
    // It starts when a new entity is created and run while there are new entities in the new_entity vector.
    // It stops till next add_entity is called.
    std::thread listener_thread_;

    //! It notifies the Callback Thread that there are callbacks available
    mutable std::condition_variable cv_callback_;
    //! Mutex asociated with \c cv_callback_
    mutable std::mutex callback_mutex_;

    //! It notifies the Callback Thread that must start
    mutable std::condition_variable cv_callback_start_;
    //! Mutex asociated with \c cv_callback_start_
    mutable std::mutex callback_mutex_start_;
};

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_MONITOR_COMPLEXMOCK_ENTITYCOLLECTOR_HPP_
