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
    qDebug() << "PARTICIPANT " << backend::backend_id_to_models_id(participant_id) << " DISCOVERED";
    engine_->add_callback(Callback(participant_id, EntityKind::PARTICIPANT));

    static_cast<void>(domain_id);
    static_cast<void>(status);
}

void Listener::on_datareader_discovery(
        EntityId domain_id,
        EntityId datareader_id,
        const Status& status)
{
    qDebug() << "DATAREADER " << backend::backend_id_to_models_id(datareader_id) << " DISCOVERED";
    engine_->add_callback(Callback(datareader_id, EntityKind::DATAREADER));

    static_cast<void>(domain_id);
    static_cast<void>(status);
}

void Listener::on_datawriter_discovery(
        EntityId domain_id,
        EntityId datawriter_id,
        const Status& status)
{
    qDebug() << "DATAWRITER " << backend::backend_id_to_models_id(datawriter_id) << " DISCOVERED";
    engine_->add_callback(Callback(datawriter_id, EntityKind::DATAWRITER));

    static_cast<void>(domain_id);
    static_cast<void>(status);
}

void Listener::on_host_discovery(
        EntityId participant_id,
        EntityId host_id,
        const Status& status)
{
    qDebug() << "HOST " << backend::backend_id_to_models_id(host_id) << " DISCOVERED";
    engine_->add_callback(Callback(host_id, EntityKind::HOST));

    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_user_discovery(
        EntityId participant_id,
        EntityId user_id,
        const Status& status)
{
    qDebug() << "USER " << backend::backend_id_to_models_id(user_id) << " DISCOVERED";
    engine_->add_callback(Callback(user_id, EntityKind::USER));

    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_process_discovery(
        EntityId participant_id,
        EntityId process_id,
        const Status& status)
{
    qDebug() << "PROCESS " << backend::backend_id_to_models_id(process_id) << " DISCOVERED";
    engine_->add_callback(Callback(process_id, EntityKind::PROCESS));

    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_locator_discovery(
        EntityId participant_id,
        EntityId locator_id,
        const Status& status)
{
    qDebug() << "LOCATOR " << backend::backend_id_to_models_id(locator_id) << " DISCOVERED";
    engine_->add_callback(Callback(locator_id, EntityKind::LOCATOR));

    static_cast<void>(participant_id);
    static_cast<void>(status);
}

void Listener::on_topic_discovery(
        EntityId domain_id,
        EntityId topic_id,
        const Status& status)
{
    qDebug() << "TOPIC " << backend::backend_id_to_models_id(topic_id) << " DISCOVERED";
    engine_->add_callback(Callback(topic_id, EntityKind::TOPIC));

    static_cast<void>(domain_id);
    static_cast<void>(status);
}

} //namespace backend
