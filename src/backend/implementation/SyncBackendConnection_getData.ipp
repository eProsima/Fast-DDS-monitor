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
 * @file SyncBackendConnection_updateAll.cpp
 */

#include <QDebug>

#include <fastdds_statistics_backend/StatisticsBackend.hpp>
#include <fastdds_statistics_backend/exception/Exception.hpp>

#include <fastdds_monitor/backend/backend_utils.h>
#include <fastdds_monitor/backend/SyncBackendConnection.h>
#include <fastdds_monitor/model/ListModel.h>
#include <fastdds_monitor/model/statistics/EntityItem.h>

namespace backend {

using namespace eprosima::statistics_backend;
using namespace models;

bool SyncBackendConnection::update_get_data_dialog_entity_id(
        models::ListModel* entity_model,
        EntityKind entity_kind,
            bool inactive_visible /* true */)
{
    bool changed = false;

    for (auto entity_id : get_entities(entity_kind, ID_ALL))
    {
        // Only get entities active if requested so
        if (inactive_visible || get_alive(entity_id))
        {
            entity_model->appendRow(new EntityItem(entity_id, entity_kind, get_info(entity_id)));
            changed = true;
        }
    }

    return changed;
}

} //namespace backend
