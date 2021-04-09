#ifndef LISTENER_H
#define LISTENER_H

#include <fastdds-statistics-backend/listener/PhysicalListener.hpp>

#include <iostream>

namespace backend {

using namespace eprosima::statistics_backend;

class Listener : public PhysicalListener
{
    void on_host_discovery(
            EntityId participant_id,
            EntityId host_id,
            const Status& status) override;

    void on_user_discovery(
            EntityId participant_id,
            EntityId user_id,
            const Status& status) override;

    void on_process_discovery(
            EntityId participant_id,
            EntityId process_id,
            const Status& status) override;

    void on_locator_discovery(
            EntityId participant_id,
            EntityId locator_id,
            const Status& status) override;

    void on_topic_discovery(
            EntityId domain_id,
            EntityId topic_id,
            const Status& status) override;

    void on_participant_discovery(
            EntityId domain_id,
            EntityId participant_id,
            const Status& status) override;

    void on_datareader_discovery(
            EntityId domain_id,
            EntityId datareader_id,
            const Status& status) override;

    void on_datawriter_discovery(
            EntityId domain_id,
            EntityId datawriter_id,
            const Status& status) override;
};

} //namespace backend

#endif // LISTENER_H
