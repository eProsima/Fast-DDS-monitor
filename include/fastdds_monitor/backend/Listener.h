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
 * @file Listener.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_BACKEND_LISTENER_H
#define _EPROSIMA_FASTDDS_MONITOR_BACKEND_LISTENER_H

#include <iostream>

#include <fastdds_statistics_backend/listener/PhysicalListener.hpp>

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
    Listener(
            Engine* engine);

    //! Callback when a new Host is discovered
    void on_host_discovery(
            EntityId host_id,
            const Status& status) override;

    //! Callback when a new User is discovered
    void on_user_discovery(
            EntityId user_id,
            const Status& status) override;

    //! Callback when a new Process is discovered
    void on_process_discovery(
            EntityId process_id,
            const Status& status) override;

    //! Callback when a new Locator is discovered
    void on_locator_discovery(
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

    //! Callback when a status is reported
    void on_status_reported(
            EntityId domain_id,
            EntityId entity_id,
            StatusKind data_kind) override;

    //! Callback when an alert is triggered
    void on_alert_triggered(
            EntityId domain_id,
            EntityId entity_id,
            AlertInfo& alert,
            const std::string& data) override;

    //! Callback when an alert is unmatched
    void on_alert_unmatched(
            EntityId domain_id,
            AlertInfo& alert) override;

protected:

    //! Engine reference
    Engine* engine_;
};

} //namespace backend

#endif // _EPROSIMA_FASTDDS_MONITOR_BACKEND_LISTENER_H
