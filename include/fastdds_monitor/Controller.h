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
 * @file Controller.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_CONTROLLER_H
#define _EPROSIMA_FASTDDS_MONITOR_CONTROLLER_H

#include <QDebug>
#include <QMap>
#include <QObject>
#include <QtCharts/QVXYModelMapper>

#include <fastdds_monitor/backend/backend_types.h>

class Engine;

enum class ErrorType : int
{
    GENERIC = 0,                    //! Generic error, just show the message
    INIT_MONITOR = 1,               //! Error in @c init_monitor. Reopen the @c init dds monitor dialog
    INIT_DS_MONITOR = 2,            //! Error in @c init_monitor. Reopen the @c init discovery server monitor dialog
    INIT_MONITOR_WITH_PROFILE = 3   //! Error in @c init_monitor_with_profile. Reopen the @c init dds monitor dialog with profile
};

/**
 * Class to connect the QML js view with the main Engine class.
 * All the methods in the class will be called by the interaction with the view and will call methods in the Engine.
 */
class Controller : public QObject
{
    Q_OBJECT

public:

    //! Standard QObject constructor with a reference to the Engine object
    Controller(
            Engine* engine,
            QObject* parent = nullptr)
        : QObject(parent)
        , engine_(engine)
    {
    }

    //! Returns the last error logged
    void send_error(
            QString error_msg,
            ErrorType error_type = ErrorType::GENERIC);

    //! Status counters displayed in the QML
    struct StatusCounters
    {
        std::map<backend::EntityId, uint32_t> errors;
        std::map<backend::EntityId, uint32_t> warnings;
        // Represents the subset of errors that a entity shares with other entities, and are deleted when the entity becomes inactive
        // Fist key is the entity id, second key is the remote entity guid and value is the number of errors shared
        std::map<backend::EntityId, std::map<std::string, uint32_t>> shared_errors;
        int32_t total_errors = 0;
        int32_t total_warnings = 0;
    }
    status_counters;

public slots:

    // Methods to be called from QML

    //! Slot called by init a monitor with a domain number
    void init_monitor(
            int domain,
            QVariantMap advanced_options);

    //! Slot called when initializing a monitor for a Discovery Server network
    void init_monitor(
            QString discovery_server_locators);

    //! Slot called when initializing a monitor with a profile name
    void init_monitor_with_profile(
            QString profile_name);

    //! Load an XML file containing DDS profiles
    void load_xml_profiles_file(
            QString file_path);

    //! Slot called when a Host entity is pressed
    void host_click(
            QString id);
    //! Slot called when a User entity is pressed
    void user_click(
            QString id);
    //! Slot called when a Process entity is pressed
    void process_click(
            QString id);

    //! Slot called when a Domain entity is pressed
    void domain_click(
            QString id);
    //! Slot called when a Topic entity is pressed
    void topic_click(
            QString id);

    //! Slot called when a Participant entity is pressed
    void participant_click(
            QString id);
    //! Slot called when a Endpoint entity is pressed
    void endpoint_click(
            QString id);
    //! Slot called when a Locator entity is pressed
    void locator_click(
            QString id);

    //! Slot called when refresh button is pressed
    void refresh_click();

    //! Slot to remove all inactive entities from database.
    void clear_entities();

    //! Clear all statistics data of all entities received before a time given.
    void clear_statistics_data(
            quint64 time = 0);

    //! Slot to clear the monitor logging information
    void clear_log();

    //! Slot to clear the issues list
    void clear_issues();

    //! Slot called when chart is to be created and ids mst be updated by an entity kind
    void update_available_entity_ids(
            QString entity_kind,
            QString entity_model_id);

    //! Get max qreal possible number
    static qreal get_max_real();

    //! Get max qreal possible number
    static qreal get_min_real();

    //! Get max quint64 possible number
    static quint64 get_max_uint();

    //! Get max quint64 possible number
    static quint64 get_min_uint();

    //! Slot called when chart is to be built
    QtCharts::QVXYModelMapper* add_statistics_data(
            quint64 chartbox_id,
            QString data_kind,
            QString source_entity_id,
            QString target_entity_id,
            quint16 bins,
            quint64 startTime,
            bool startTimeDefault,
            quint64 endTime,
            bool endTimeDefault,
            QString statisticKind);

    //! Returns the eProsima Fast DDS version used to compile the Monitor
    QString fastdds_version();

    //! Returns the eProsima Fast DDS Statistics Backend version used to compile the Monitor
    QString fastdds_statistics_backend_version();

    //! Returns the Qt version used to compile the Monitor
    QString qt_version();

    //! Returns the eProsima Fast DDS Monitor version used to compile the Monitor
    QString fastdds_monitor_version();

    //! Returns the system information for which Fast DDS is built
    QString system_info();

    //! Returns the date on which Fast DDS Monitor was built
    QString build_date();

    //! Returns the Fast DDS Monitor GitHub commit built
    QString git_commit();

    //! Whether the inactive entities must be shown or hidden
    bool inactive_visible();

    //! Change \c inactive_visible status
    void change_inactive_visible();

    //! Whether metatraffic must be shown or hidden
    bool metatraffic_visible();

    //! Change \c metatraffic_visible status
    void change_metatraffic_visible();

    //! Whether the ROS 2 demangling is active
    bool ros2_demangling_active();

    //! Change \c ros2_demangling_active status
    void change_ros2_demangling();

    //! Call engine to refresh summary
    void refresh_summary();

    //! Call engine to update a dynamic chartbox
    void update_dynamic_chartbox(
            quint64 chartbox_id,
            quint64 time_to);

    //! Change alias
    void set_alias(
            QString entity_id,
            QString new_alias,
            QString entity_kind);

    //! Give a string with the name of the unit magnitud in which each DataKind is measured
    QString get_data_kind_units(
            QString data_kind);

    /**
     * @brief Export the series given to a new csv file
     *
     * Export one or multiple series to a new csv file.
     * Each series to export is given in a vector as chartbox id and series index to get the data from the models.
     * Each series to export is given with its headers in order to save them in the csv and can import the file.
     *
     * @param file_name         path and name to the new csv file
     * @param chartbox_ids      ids of the chartboxes of each series
     * @param series_indexes    indexes of the series inside each chartbox
     * @param data_kinds        DataKind that refers to the each series
     * @param chartbox_names    Title of the chartbox this series belongs
     * @param label_names       Label of each series
     */
    void save_csv(
            QString file_name,
            QList<quint64> chartbox_ids,
            QList<quint64> series_indexes,
            QStringList data_kinds,
            QStringList chartbox_names,
            QStringList label_names);

    /**
     * @brief Dump Fast DDS Statistics Backend's database to a file.
     *
     * @param file_name The name of the file where the database is dumped.
     * @param clear If true, clear all the statistics data of all entities.
     */
    void dump(
            QString file_name,
            bool clear);

    //! Retrive a string list containing the transport protocols supported by the Statistics Backend Discovery Server.
    QStringList ds_supported_transports();

    //! Retrive a string list containing the available statistic kinds.
    QStringList get_statistic_kinds();

    //! Retrive a string list containing the available data kinds.
    QStringList get_data_kinds();

    //! Returns whether the data kind entered requires a target entity to be defined.
    bool data_kind_has_target(
            const QString& data_kind);

    /**
     * @brief Export the series given to a new csv file
     *
     * Export one or multiple series to a new csv file.
     * Each series to export is given in a vector as chartbox id and series index to get the data from the models.
     * Each series to export is given with its headers in order to save them in the csv and can import the file.
     *
     * @param series_id         path and name to the new csv file
     * @param series_id         ids of the chartboxes of each series
     * @param series_indexes    indexes of the series inside each chartbox
     * @param data_kinds        DataKind that refers to the each series
     * @param chartbox_names    Title of the chartbox this series belongs
     * @param label_names       Label of each series
     */
    void change_max_points(
            quint64 chartbox_id,
            quint64 series_id,
            quint64 new_max_point);


    //! Request to backend the latest domain view JSON to build the graph
    QString get_domain_view_graph (
            QString domain_id);

    QString get_type_idl (
            QString entity_id);

    QString get_ros2_type_idl (
            QString entity_id);

    QString get_ros2_type_name (
            QString entity_id);

    QString get_endpoint_topic_id(
            QString endpoint_id);

    QString get_domain_id(
            QString entity_id);

    QString get_name(
            QString entity_id);

    QString get_data_type_name(
            QString entity_id);

signals:

    //! Signal to show the Error Dialog
    void error(
            QString error_msg,
            int error_type);

    //! Signal to inform qml that a new monitor has been initialized
    void monitorInitialized();

    //! Signal to notify status counters have been updated
    void update_status_counters(
            QString errors,
            QString warnings);

protected:

    //! Reference to \c Engine object
    Engine* engine_;
};

#endif // _EPROSIMA_FASTDDS_MONITOR_CONTROLLER_H
