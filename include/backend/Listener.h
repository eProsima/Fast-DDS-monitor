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
 * @file Listener.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_BACKEND_LISTENER_H
#define _EPROSIMA_FASTDDS_MONITOR_BACKEND_LISTENER_H

#include <iostream>

#include <fastdds-statistics-backend/listener/PhysicalListener.hpp>

class Engine;

namespace backend {

using namespace eprosima::statistics_backend;

/**
 * @brief Listener class to receieve the callbacks from the backend
 *
 * Only the discovery callbacks are implemented, the data callbacks will be added in future versions.
 * Every callback calls an \c Engine method that emits a signal, so the process of the callback is
 * done in the main view thread, allowing the automatic refresh of the data in the view.
 */
class Listener : public PhysicalListener
{
public:

    //! Standard constructor with reference to the main Engine
    Listener(Engine* engine);

    //! Callback when a new Host is discovered
    void on_host_discovery(
            EntityId participant_id,
            EntityId host_id,
            const Status& status) override;

    //! Callback when a new User is discovered
    void on_user_discovery(
            EntityId participant_id,
            EntityId user_id,
            const Status& status) override;

    //! Callback when a new Process is discovered
    void on_process_discovery(
            EntityId participant_id,
            EntityId process_id,
            const Status& status) override;

    //! Callback when a new Locator is discovered
    void on_locator_discovery(
            EntityId participant_id,
            EntityId locator_id,
            const Status& status) override;

    //! Callback when a new Topic is discovered
    void on_topic_discovery(
            EntityId domain_id,
            EntityId topic_id,
            const Status& status) override;

    //! Callback when a new Participant is discovered
    void on_participant_discovery(
            EntityId domain_id,
            EntityId participant_id,
            const Status& status) override;

    //! Callback when a new DataReader is discovered
    void on_datareader_discovery(
            EntityId domain_id,
            EntityId datareader_id,
            const Status& status) override;

    //! Callback when a new DataWriter is discovered
    void on_datawriter_discovery(
            EntityId domain_id,
            EntityId datawriter_id,
            const Status& status) override;

protected:

    //! Engine reference
    Engine* engine_;
};

} //namespace backend

#endif // _EPROSIMA_FASTDDS_MONITOR_BACKEND_LISTENER_H
