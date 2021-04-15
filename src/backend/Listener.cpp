
#include <fastdds-statistics-backend/listener/PhysicalListener.hpp>

#include <include/Engine.h>

#include <iostream>

namespace backend {

Listener::Listener(Engine* engine)
    : engine_(engine)
{
}

void Listener::on_participant_discovery(
        EntityId domain_id,
        EntityId participant_id,
        const Status& status)
{
    qDebug() << "PARTICIPANT " << backend::id_to_QString(participant_id) << " DISCOVERED";
    engine_->add_callback(Callback(participant_id, EntityKind::PARTICIPANT));

    static_cast<void>(domain_id);
    static_cast<void>(status);
}

void Listener::on_datareader_discovery(
        EntityId domain_id,
        EntityId datareader_id,
        const Status& status)
{
    qDebug() << "DATAREADER " << backend::id_to_QString(datareader_id) << " DISCOVERED";
    engine_->add_callback(Callback(datareader_id, EntityKind::DATAREADER));

    static_cast<void>(domain_id);
    static_cast<void>(status);
}

void Listener::on_datawriter_discovery(
        EntityId domain_id,
        EntityId datawriter_id,
        const Status& status)
{
    qDebug() << "DATAWRITER " << backend::id_to_QString(datawriter_id) << " DISCOVERED";
    engine_->add_callback(Callback(datawriter_id, EntityKind::DATAWRITER));

    static_cast<void>(domain_id);
    static_cast<void>(status);
}

void Listener::on_host_discovery(
        EntityId participant_id,
        EntityId host_id,
        const Status& status)
{
    qDebug() << "HOST " << backend::id_to_QString(host_id) << " DISCOVERED";
    engine_->add_callback(Callback(host_id, EntityKind::HOST));

    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_user_discovery(
        EntityId participant_id,
        EntityId user_id,
        const Status& status)
{
    qDebug() << "USER " << backend::id_to_QString(user_id) << " DISCOVERED";
    engine_->add_callback(Callback(user_id, EntityKind::USER));

    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_process_discovery(
        EntityId participant_id,
        EntityId process_id,
        const Status& status)
{
    qDebug() << "PROCESS " << backend::id_to_QString(process_id) << " DISCOVERED";
    engine_->add_callback(Callback(process_id, EntityKind::PROCESS));

    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_locator_discovery(
        EntityId participant_id,
        EntityId locator_id,
        const Status& status)
{
    qDebug() << "LOCATOR " << backend::id_to_QString(locator_id) << " DISCOVERED";
    engine_->add_callback(Callback(locator_id, EntityKind::LOCATOR));

    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_topic_discovery(
        EntityId domain_id,
        EntityId topic_id,
        const Status& status)
{
    qDebug() << "TOPIC " << backend::id_to_QString(topic_id) << " DISCOVERED";
    engine_->add_callback(Callback(topic_id, EntityKind::TOPIC));

    static_cast<void>(domain_id);
    static_cast<void>(status);
}

} //namespace backend
