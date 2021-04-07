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
 * @file Database.hpp
 */

#include <atomic>
#include <mutex>
#include <thread>
#include <condition_variable>

#include <fastdds-statistics-backend/listener/PhysicalListener.hpp>
#include <fastdds-statistics-backend/types/types.hpp>

#include "../entities/headers/Entity.hpp"

#ifndef _EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_ENTITYCOLLECTOR_HPP_
#define _EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_ENTITYCOLLECTOR_HPP_

namespace eprosima {
namespace statistics_backend {

#define DATA_GENERATION_TIME 10

class Database
{
public:

    static Database* get_instance()
    {
        static Database instance;
        return &instance;
    }

    void listener(PhysicalListener* listener);

    EntityId add_domain();

    std::vector<EntityId> get_entities(
        EntityKind entity_type,
        EntityId entity_id);

    Info get_info(EntityId entity_id);

    std::map<EntityId, EntityPointer>& get_all_entities();

    void start();
    void stop();

    int64_t next_id();

    EntityPointer get_entity(EntityId id);

protected:

    Database();

    ~Database();

    void generate_random_data_thread();
    void callback_listener_thread();

    void add_entity(EntityPointer entity);

    void add_entities(std::vector<EntityPointer> entities);

    size_t count_domains();
    size_t count_entities();

private:

    std::vector<EntityId> domains_;
    std::map<EntityId, EntityPointer> entities_;
    int64_t last_id_;
    PhysicalListener* listener_;

    std::thread generate_data_thread_;
    std::thread listener_thread_;
    std::recursive_mutex data_mutex_;
    std::atomic<bool> run_;

    mutable std::condition_variable cv_;
    mutable std::mutex run_mutex_;
};

} // namespace statistics_backend
} // namespace eprosima

#endif //_EPROSIMA_FASTDDS_STATISTICS_BACKEND_COMPLEXMOCK_ENTITYCOLLECTOR_HPP_