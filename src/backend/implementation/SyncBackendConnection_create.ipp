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
 * @file SyncBackendConnection.cpp
 */

#include <iostream>

#include <QDebug>

#include <fastdds_statistics_backend/StatisticsBackend.hpp>
#include <fastdds_statistics_backend/exception/Exception.hpp>

#include <fastdds_monitor/backend/backend_utils.h>
#include <fastdds_monitor/backend/SyncBackendConnection.h>
#include <fastdds_monitor/model/dds/EndpointModelItem.h>
#include <fastdds_monitor/model/dds/LocatorModelItem.h>
#include <fastdds_monitor/model/dds/ParticipantModelItem.h>
#include <fastdds_monitor/model/ListItem.h>
#include <fastdds_monitor/model/ListModel.h>
#include <fastdds_monitor/model/logical/DomainModelItem.h>
#include <fastdds_monitor/model/logical/TopicModelItem.h>
#include <fastdds_monitor/model/physical/HostModelItem.h>
#include <fastdds_monitor/model/physical/ProcessModelItem.h>
#include <fastdds_monitor/model/physical/UserModelItem.h>
#include <fastdds_monitor/model/statistics/EntityItem.h>
#include <fastdds_monitor/model/SubListedListModel.h>
#include <fastdds_monitor/model/tree/TreeModel.h>

namespace backend {

using namespace eprosima::statistics_backend;
using namespace models;

ListItem* SyncBackendConnection::create_host_data_(
        EntityId id)
{
    qDebug() << "Creating Host " << backend::backend_id_to_models_id(id);
    return new HostModelItem(id, get_info(id));
}

ListItem* SyncBackendConnection::create_user_data_(
        EntityId id)
{
    qDebug() << "Creating User " << backend::backend_id_to_models_id(id);
    return new UserModelItem(id, get_info(id));
}

ListItem* SyncBackendConnection::create_process_data_(
        EntityId id)
{
    qDebug() << "Creating Process " << backend::backend_id_to_models_id(id);
    return new ProcessModelItem(id, get_info(id));
}

ListItem* SyncBackendConnection::create_domain_data_(
        EntityId id)
{
    qDebug() << "Creating Domain " << backend::backend_id_to_models_id(id);
    return new DomainModelItem(id, get_info(id));
}

ListItem* SyncBackendConnection::create_topic_data_(
        EntityId id)
{
    qDebug() << "Creating Topic " << backend::backend_id_to_models_id(id);
    return new TopicModelItem(id, get_info(id));
}

ListItem* SyncBackendConnection::create_participant_data_(
        backend::EntityId id)
{
    qDebug() << "Creating Participant " << backend::backend_id_to_models_id(id);
    return new ParticipantModelItem(id, get_info(id));
}

ListItem* SyncBackendConnection::create_datawriter_data_(
        backend::EntityId id)
{
    qDebug() << "Creating DataWriter " << backend::backend_id_to_models_id(id);
    return new EndpointModelItem(id, get_info(id), EntityKind::DATAWRITER);
}

ListItem* SyncBackendConnection::create_datareader_data_(
        backend::EntityId id)
{
    qDebug() << "Creating DataReader " << backend::backend_id_to_models_id(id);
    return new EndpointModelItem(id, get_info(id), EntityKind::DATAREADER);
}

ListItem* SyncBackendConnection::create_locator_data_(
        backend::EntityId id)
{
    qDebug() << "Creating Locator " << backend::backend_id_to_models_id(id);
    return new LocatorModelItem(id, get_info(id));
}

} //namespace backend
