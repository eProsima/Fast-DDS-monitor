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
#include <QStringBuilder>
#include <QtGlobal>

#include <fastdds_monitor/config.h>
#include <fastdds_statistics_backend/config.h>
#include <fastrtps/config.h>

#include <fastdds_monitor/Controller.h>
#include <fastdds_monitor/Engine.h>
#include <fastdds_monitor/utils.h>

void Controller::init_monitor(
        int domain)
{
    engine_->init_monitor(domain);
}

void Controller::init_monitor(
        QString locators)
{
    engine_->init_monitor(locators);
}

void Controller::host_click(
        QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::HOST);
}

void Controller::user_click(
        QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::USER);
}

void Controller::process_click(
        QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::PROCESS);
}

void Controller::domain_click(
        QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::DOMAIN);
}

void Controller::topic_click(
        QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::TOPIC);
}

void Controller::participant_click(
        QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::PARTICIPANT);
}

void Controller::endpoint_click(
        QString id)
{
    // WARNING: we do not know if it is DataWriter or DataReader
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::DATAWRITER);
}

void Controller::locator_click(
        QString id)
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

QString Controller::fastdds_version()
{
    return utils::to_QString(FASTRTPS_VERSION_STR);
}

QString Controller::fastdds_statistics_backend_version()
{
    return utils::to_QString(FASTDDS_STATISTICS_BACKEND_VERSION_STR);
}

QString Controller::qt_version()
{
    return utils::to_QString(qVersion());
}

QString Controller::fastdds_monitor_version()
{
    return utils::to_QString(FASTDDS_MONITOR_VERSION_STR);
}

QString Controller::system_info()
{
    return utils::to_QString(SYSTEM_NAME) % " "
           % utils::to_QString(SYSTEM_PROCESSOR) % " "
           % utils::to_QString(SYSTEM_VERSION);
}

QString Controller::build_date()
{
    return utils::to_QString(BUILD_DATE);
}

QString Controller::git_commit()
{
    return utils::to_QString(GIT_COMMIT_HASH);
}

void Controller::refresh_summary()
{
    engine_->refresh_summary();
}

QString Controller::error_message()
{
    return last_error_;
}

void Controller::set_error(QString error_msg)
{
    last_error_ = error_msg;
    emit error();
}
