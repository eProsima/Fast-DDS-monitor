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

#include <include/Controller.h>
#include <include/Engine.h>

void Controller::init_monitor(int domain)
{
    engine_->init_monitor(domain);
}

void Controller::init_monitor(QString locators)
{
    engine_->init_monitor(locators);
}

void Controller::host_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::HOST);
}

void Controller::user_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::USER);
}

void Controller::process_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::PROCESS);
}

void Controller::domain_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::DOMAIN);
}

void Controller::topic_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::TOPIC);
}

void Controller::participant_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::PARTICIPANT);
}

void Controller::endpoint_click(QString id)
{
    // WARNING: we do not know if it is DataWriter or DataReader
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::DATAWRITER);
}

void Controller::locator_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::LOCATOR);
}

void Controller::update_available_entity_ids(
        QString entity_kind,
        QString entity_model_id)
{
    engine_->on_selected_entity_kind(backend::string_to_entity_kind(entity_kind), entity_model_id);
}

void Controller::refresh_click()
{
    engine_->refresh_engine();
}

void Controller::add_statistics_data(
        QString data_kind,
        QString source_entity_id,
        QString target_entity_id,
        quint16 bins,
        quint64 start_time,
        bool start_time_default,
        quint64 end_time,
        bool end_time_default,
        QString statistic_kind)
{

    qDebug() << "Data Kind: " << data_kind << "\n" <<
                "Source Entity Id: " << source_entity_id << "\n" <<
                "Target Entity Id: " << target_entity_id << "\n" <<
                "Bins: " << bins << "\n" <<
                "Time Start: " << start_time << "\n" <<
                "Time Start Default: " << start_time_default << "\n" <<
                "End Start: " << end_time << "\n" <<
                "End Start Default: " << end_time_default << "\n" <<
                "Statistics Kind: " << statistic_kind;


    engine_->on_add_statistics_data_series(
                backend::string_to_data_kind(data_kind),
                backend::models_id_to_backend_id(source_entity_id),
                backend::models_id_to_backend_id(target_entity_id),
                bins,
                start_time,
                start_time_default,
                end_time,
                end_time_default,
                backend::string_to_statistic_kind(statistic_kind));
}
