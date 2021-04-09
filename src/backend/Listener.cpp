
#include <fastdds-statistics-backend/listener/PhysicalListener.hpp>

#include <include/Engine.h>

#include <iostream>

namespace backend {

void Listener::on_participant_discovery(
        EntityId domain_id,
        EntityId participant_id,
        const Status& status)
{
    std::cout << "PARTICIPANT " << participant_id << " DISCOVERED" << std::endl;
    Engine::get_instance()->add_callback(Callback(participant_id, EntityKind::PARTICIPANT));

    static_cast<void>(domain_id);
    static_cast<void>(status);
}

void Listener::on_datareader_discovery(
        EntityId domain_id,
        EntityId datareader_id,
        const Status& status)
{
    std::cout << "DATAREADER " << datareader_id << " DISCOVERED" << std::endl;
    Engine::get_instance()->add_callback(Callback(datareader_id, EntityKind::DATAREADER));

    static_cast<void>(domain_id);
    static_cast<void>(status);
}

void Listener::on_datawriter_discovery(
        EntityId domain_id,
        EntityId datawriter_id,
        const Status& status)
{
    std::cout << "DATAWRITER " << datawriter_id << " DISCOVERED" << std::endl;
    Engine::get_instance()->add_callback(Callback(datawriter_id, EntityKind::DATAWRITER));

    static_cast<void>(domain_id);
    static_cast<void>(status);
}

void Listener::on_host_discovery(
        EntityId participant_id,
        EntityId host_id,
        const Status& status)
{
    std::cout << "HOST " << host_id << " DISCOVERED" << std::endl;
    Engine::get_instance()->add_callback(Callback(host_id, EntityKind::HOST));

    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_user_discovery(
        EntityId participant_id,
        EntityId user_id,
        const Status& status)
{
    std::cout << "USER " << user_id << " DISCOVERED" << std::endl;
    Engine::get_instance()->add_callback(Callback(user_id, EntityKind::USER));

    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_process_discovery(
        EntityId participant_id,
        EntityId process_id,
        const Status& status)
{
    std::cout << "PROCESS " << process_id << " DISCOVERED" << std::endl;
    Engine::get_instance()->add_callback(Callback(process_id, EntityKind::PROCESS));

    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_locator_discovery(
        EntityId participant_id,
        EntityId locator_id,
        const Status& status)
{
    std::cout << "LOCATOR " << locator_id << " DISCOVERED" << std::endl;
    Engine::get_instance()->add_callback(Callback(locator_id, EntityKind::LOCATOR));

    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_topic_discovery(
        EntityId domain_id,
        EntityId topic_id,
        const Status& status)
{
    std::cout << "TOPIC " << topic_id << " DISCOVERED" << std::endl;
    Engine::get_instance()->add_callback(Callback(topic_id, EntityKind::TOPIC));

    static_cast<void>(domain_id);
    static_cast<void>(status);
}

} //namespace backend
