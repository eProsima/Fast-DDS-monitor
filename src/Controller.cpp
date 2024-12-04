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
#include <QStringBuilder>
#include <QtGlobal>

#include <fastdds_monitor/config.h>
#include <fastdds_statistics_backend/config.h>
#include <fastdds/config.hpp>

#include <fastdds_monitor/Controller.h>
#include <fastdds_monitor/Engine.h>
#include <fastdds_monitor/utils.h>

void Controller::init_monitor(
        int domain)
{
    engine_->init_monitor(domain);
}

void Controller::init_monitor(
        QString discovery_server_locators)
{
    engine_->init_monitor(discovery_server_locators);
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
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::DOMAIN_ENTITY);
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

void Controller::clear_entities()
{
    engine_->clear_entities();
}

void Controller::clear_statistics_data(
        quint64 time_to)
{
    engine_->clear_statistics_data(time_to);
}

void Controller::clear_log()
{
    engine_->clear_log();
}

void Controller::clear_issues()
{
    engine_->clear_issues();
}

qreal Controller::get_max_real()
{
    return std::numeric_limits<qreal>::max();
}

qreal Controller::get_min_real()
{
    return std::numeric_limits<qreal>::lowest();
}

quint64 Controller::get_max_uint()
{
    return std::numeric_limits<quint64>::max();
}

quint64 Controller::get_min_uint()
{
    return std::numeric_limits<quint64>::min();
}

QtCharts::QVXYModelMapper* Controller::add_statistics_data(
        quint64 chartbox_id,
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
    qDebug() << "Call add_statistics_data with datakind: " << data_kind;
    return engine_->on_add_statistics_data_series(
        chartbox_id,
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
    return utils::to_QString(FASTDDS_VERSION_STR);
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

bool Controller::inactive_visible()
{
    return engine_->inactive_visible();
}

void Controller::change_inactive_visible()
{
    engine_->change_inactive_visible();
}

bool Controller::metatraffic_visible()
{
    return engine_->metatraffic_visible();
}

void Controller::change_metatraffic_visible()
{
    engine_->change_metatraffic_visible();
}

void Controller::refresh_summary()
{
    engine_->refresh_summary();
}

void Controller::send_error(
        QString error_msg,
        ErrorType error_type /*= GENERIC*/)
{
    // Must convert enumeration to int in order to qml understand it
    emit error(error_msg, static_cast<typename std::underlying_type<ErrorType>::type>(error_type));
}

void Controller::update_dynamic_chartbox(
        quint64 chartbox_id,
        quint64 time_to)
{
    engine_->update_dynamic_chartbox(chartbox_id, time_to);
}

void Controller::set_alias(
        QString entity_id,
        QString new_alias,
        QString entity_kind)
{
    engine_->set_alias(
        backend::models_id_to_backend_id(entity_id),
        utils::to_string(new_alias),
        backend::string_to_entity_kind(entity_kind));
}

QString Controller::get_data_kind_units(
        QString data_kind)
{
    return utils::to_QString(engine_->get_data_kind_units(data_kind));
}

void Controller::save_csv(
        QString file_name,
        QList<quint64> chartbox_ids,
        QList<quint64> series_indexes,
        QStringList data_kinds,
        QStringList chartbox_names,
        QStringList label_names)
{
    engine_->save_csv(
        file_name,
        chartbox_ids,
        series_indexes,
        data_kinds,
        chartbox_names,
        label_names);
}

void Controller::dump(
        QString file_name,
        bool clear)
{
    engine_->dump(
        file_name,
        clear);
}

QStringList Controller::ds_supported_transports()
{
    return utils::to_QStringList(engine_->ds_supported_transports());
}

QStringList Controller::get_statistic_kinds()
{
    return utils::to_QStringList(engine_->get_statistic_kinds());
}

QStringList Controller::get_data_kinds()
{
    return utils::to_QStringList(engine_->get_data_kinds());
}

bool Controller::data_kind_has_target(
        const QString& data_kind)
{
    return engine_->data_kind_has_target(data_kind);
}

void Controller::change_max_points(
        quint64 chartbox_id,
        quint64 series_id,
        quint64 new_max_point)
{
    return engine_->change_max_points(chartbox_id, series_id, new_max_point);
}

QString Controller::get_domain_view_graph(
        QString entity_id)
{
    backend::Graph domain_view = engine_->get_domain_view_graph(backend::models_id_to_backend_id(entity_id));
    return QString::fromUtf8(domain_view.dump().data(), int(domain_view.dump().size()));
}

QString Controller::get_type_idl(
        QString entity_id)
{
    return utils::to_QString(engine_->get_type_idl(backend::models_id_to_backend_id(entity_id)));
}

QString Controller::get_endpoint_topic_id(
        QString endpoint_id)
{
    return engine_->get_endpoint_topic_id(endpoint_id);
}

QString Controller::get_domain_id(
        QString entity_id)
{
    return engine_->get_domain_id(entity_id);
}

QString Controller::get_name(
        QString entity_id)
{
    return utils::to_QString(engine_->get_name(backend::models_id_to_backend_id(entity_id)));
}

QString Controller::get_data_type_name(
        QString entity_id)
{
    return utils::to_QString(engine_->get_data_type_name(backend::models_id_to_backend_id(entity_id)));
}
