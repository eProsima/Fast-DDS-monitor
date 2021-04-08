
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

    static_cast<void>(domain_id);
    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_datareader_discovery(
        EntityId domain_id,
        EntityId datareader_id,
        const Status& status)
{
    std::cout << "DATAREADER " << datareader_id << " DISCOVERED" << std::endl;

//    Engine::get_instance()->update_endpoint_data(domain_id);
    Engine::get_instance()->add_callback(Callback(datareader_id, EntityKind::DATAREADER));

    static_cast<void>(domain_id);
    static_cast<void>(datareader_id);
    static_cast<void>(status);
}

void Listener::on_datawriter_discovery(
        EntityId domain_id,
        EntityId datawriter_id,
        const Status& status)
{
    std::cout << "DATAWRITER " << datawriter_id << " DISCOVERED" << std::endl;

//    Engine::get_instance()->update_endpoint_data(domain_id);
    Engine::get_instance()->add_callback(Callback(datawriter_id, EntityKind::DATAWRITER));

    static_cast<void>(domain_id);
    static_cast<void>(datawriter_id);
    static_cast<void>(status);
}

void Listener::on_host_discovery(
        EntityId participant_id,
        EntityId host_id,
        const Status& status)
{
    std::cout << "HOST " << host_id << " DISCOVERED" << std::endl;

//    Engine::get_instance()->update_host_data(host_id);
    Engine::get_instance()->add_callback(Callback(host_id, EntityKind::HOST));

    static_cast<void>(participant_id);
    static_cast<void>(host_id);
    static_cast<void>(status);
}

} //namespace backend
