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

class Engine;

/**
 * Class to connect the QML js view with the main Engine class
 * All the methods in the class will be called by the interaction with the view and will call methods in the Engine
 */
class Controller : public QObject
{
    Q_OBJECT

public:

    //! Standard QObject constructor with a reference to the Engine object
    Controller(
            Engine* engine,
            QObject *parent = nullptr)
        : QObject(parent)
        , engine_(engine)
    {
    }

// Methods to be called from QML
public slots:

    //! Slot called by init a monitor with a domain number
    void init_monitor(int domain);

    //! Slot called by init a monitor with a list of locators
    void init_monitor(QString locators);

    //! Slot called when a Host entity is pressed
    void host_click(QString id);
    //! Slot called when a User entity is pressed
    void user_click(QString id);
    //! Slot called when a Process entity is pressed
    void process_click(QString id);

    //! Slot called when a Domain entity is pressed
    void domain_click(QString id);
    //! Slot called when a Topic entity is pressed
    void topic_click(QString id);

    //! Slot called when a Participant entity is pressed
    void participant_click(QString id);
    //! Slot called when a Endpoint entity is pressed
    void endpoint_click(QString id);
    //! Slot called when a Locator entity is pressed
    void locator_click(QString id);

    //! Slot called when refresh button is pressed
    void refresh_click();

    //! Slot called when chart is to be created and ids mst be updated by an entity kind
    void update_available_entity_ids(
            QString entity_kind,
            QString entity_model_id);

    //! Slot called when chart is to be built
    void add_statistics_data(
            QString data_kind,
            QString source_entity_id,
            QString target_entity_id,
            quint16 bins,
            quint64 startTime,
            bool startTimeDefault,
            quint64 endTime,
            bool endTimeDefault,
            QString statisticKind);

protected:

    //! Reference to \c Engine object
    Engine* engine_;
};

#endif // _EPROSIMA_FASTDDS_MONITOR_CONTROLLER_H
