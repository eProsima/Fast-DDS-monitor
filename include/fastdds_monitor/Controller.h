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

/**
 * @file Controller.h
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_CONTROLLER_H
#define _EPROSIMA_FASTDDS_MONITOR_CONTROLLER_H

#include <QDebug>
#include <QObject>
#include <QtCharts/QVXYModelMapper>

class Engine;

enum class ErrorType : int
{
    GENERIC = 0,            //! Generic error, just show the message
    INIT_MONITOR = 1,       //! Error in @c init_monitor. Reopen the @c init dds monitor dialog
    INIT_DS_MONITOR = 2     //! Error in @c init_monitor. Reopen the @c init discovery server monitor dialog
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

public slots:

    // Methods to be called from QML

    //! Slot called by init a monitor with a domain number
    void init_monitor(
            int domain);

    //! Slot called when initializing a monitor for a Discovery Server network
    void init_monitor(
            QString discovery_server_guid_prefix,
            QString discovery_server_locators);

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

    //! Slot to clear the monitor logging information
    void clear_log();

    //! Slot to clear the issues list
    void clear_issues();

    //! Slot called when chart is to be created and ids mst be updated by an entity kind
    void update_available_entity_ids(
            QString entity_kind,
            QString entity_model_id);

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

    //! Returns the eProsima Fast DDS version used to compile de Monitor
    QString fastdds_version();

    //! Returns the eProsima Fast DDS Statistics Backend version used to compile de Monitor
    QString fastdds_statistics_backend_version();

    //! Returns the Qt version used to compile de Monitor
    QString qt_version();

    //! Returns the eProsima Fast DDS Monitor version used to compile de Monitor
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
     * Each series to export is given in a vector as chartobox id and series index to get the data from the models.
     * Each series to export is given with its headers in order to save them in the csv and can import the file.
     *
     * @param file_name         path and name to the new csv file
     * @param chartbox_ids      ids of the chartboxes of each series
     * @param series_indexes    indexes of the serioes inside each chartbox
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

    //! Retrive a string list containing the transport protocols supported by the Statistics Backend Discovery Server.
    QStringList ds_supported_transports();

    //! Retrive a string list containing the available statistic kinds.
    QStringList get_statistic_kinds();

    //! Retrive a string list containing the available data kinds.
    QStringList get_data_kinds();

signals:

    //! Signal to show the Error Dialog
    void error(
            QString error_msg,
            int error_type);

protected:

    //! Reference to \c Engine object
    Engine* engine_;
};

#endif // _EPROSIMA_FASTDDS_MONITOR_CONTROLLER_H
