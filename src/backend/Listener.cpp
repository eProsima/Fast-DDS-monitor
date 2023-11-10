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

#include <QDebug>

#include <fastdds_statistics_backend/listener/PhysicalListener.hpp>

#include <fastdds_monitor/Engine.h>

namespace backend {

Listener::Listener(
        Engine* engine)
    : engine_(engine)
{
}

void Listener::on_participant_discovery(
        EntityId domain_id,
        EntityId participant_id,
        const Status& status)
{
    static_cast<void>(domain_id);

    if (status.current_count_change == 1)
    {
        qDebug() << "PARTICIPANT " << backend::backend_id_to_models_id(participant_id) << " DISCOVERED";
        engine_->add_callback(Callback(participant_id, EntityKind::PARTICIPANT));
    }
    else
    {
        qDebug() << "PARTICIPANT " << backend::backend_id_to_models_id(participant_id) << " update info";
        engine_->add_callback(Callback(participant_id, EntityKind::PARTICIPANT, true));
    }
}

void Listener::on_datareader_discovery(
        EntityId domain_id,
        EntityId datareader_id,
        const Status& status)
{
    static_cast<void>(domain_id);

    if (status.current_count_change == 1)
    {
        qDebug() << "DATAREADER " << backend::backend_id_to_models_id(datareader_id) << " DISCOVERED";
        engine_->add_callback(Callback(datareader_id, EntityKind::DATAREADER));
    }
    else
    {
        qDebug() << "DATAREADER " << backend::backend_id_to_models_id(datareader_id) << " update info";
        engine_->add_callback(Callback(datareader_id, EntityKind::DATAREADER, true));
    }
}

void Listener::on_datawriter_discovery(
        EntityId domain_id,
        EntityId datawriter_id,
        const Status& status)
{
    static_cast<void>(domain_id);

    if (status.current_count_change == 1)
    {
        qDebug() << "DATAWRITER " << backend::backend_id_to_models_id(datawriter_id) << " DISCOVERED";
        engine_->add_callback(Callback(datawriter_id, EntityKind::DATAWRITER));
    }
    else
    {
        qDebug() << "DATAWRITER " << backend::backend_id_to_models_id(datawriter_id) << " update info";
        engine_->add_callback(Callback(datawriter_id, EntityKind::DATAWRITER, true));
    }
}

void Listener::on_host_discovery(
        EntityId host_id,
        const Status& status)
{
    if (status.current_count_change == 1)
    {
        qDebug() << "HOST " << backend::backend_id_to_models_id(host_id) << " DISCOVERED";
        engine_->add_callback(Callback(host_id, EntityKind::HOST));
    }
    else
    {
        qDebug() << "HOST " << backend::backend_id_to_models_id(host_id) << " update info";
        engine_->add_callback(Callback(host_id, EntityKind::HOST, true));
    }
}

void Listener::on_user_discovery(
        EntityId user_id,
        const Status& status)
{
    if (status.current_count_change == 1)
    {
        qDebug() << "USER " << backend::backend_id_to_models_id(user_id) << " DISCOVERED";
        engine_->add_callback(Callback(user_id, EntityKind::USER));
    }
    else
    {
        qDebug() << "USER " << backend::backend_id_to_models_id(user_id) << " update info";
        engine_->add_callback(Callback(user_id, EntityKind::USER, true));
    }
}

void Listener::on_process_discovery(
        EntityId process_id,
        const Status& status)
{
    if (status.current_count_change == 1)
    {
        qDebug() << "PROCESS " << backend::backend_id_to_models_id(process_id) << " DISCOVERED";
        engine_->add_callback(Callback(process_id, EntityKind::PROCESS));
    }
    else
    {
        qDebug() << "PROCESS " << backend::backend_id_to_models_id(process_id) << " update info";
        engine_->add_callback(Callback(process_id, EntityKind::PROCESS, true));
    }
}

void Listener::on_locator_discovery(
        EntityId locator_id,
        const Status& status)
{
    if (status.current_count_change == 1)
    {
        qDebug() << "LOCATOR " << backend::backend_id_to_models_id(locator_id) << " DISCOVERED";
        engine_->add_callback(Callback(locator_id, EntityKind::LOCATOR));
    }
    else
    {
        qDebug() << "LOCATOR " << backend::backend_id_to_models_id(locator_id) << " update info";
        engine_->add_callback(Callback(locator_id, EntityKind::LOCATOR, true));
    }
}

void Listener::on_topic_discovery(
        EntityId domain_id,
        EntityId topic_id,
        const Status& status)
{
    static_cast<void>(domain_id);

    if (status.current_count_change == 1)
    {
        qDebug() << "TOPIC " << backend::backend_id_to_models_id(topic_id) << " DISCOVERED";
        engine_->add_callback(Callback(topic_id, EntityKind::TOPIC));
    }
    else
    {
        qDebug() << "TOPIC " << backend::backend_id_to_models_id(topic_id) << " update info";
        engine_->add_callback(Callback(topic_id, EntityKind::TOPIC, true));
    }
}

void Listener::on_status_reported(
        EntityId domain_id,
        EntityId entity_id,
        StatusKind status_kind)
{
    engine_->add_callback(ProblemCallback(domain_id, entity_id, status_kind));
}

} //namespace backend
