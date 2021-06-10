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
 * @file SubListedListModel.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_SUBLISTEDLISTMODEL_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_SUBLISTEDLISTMODEL_H

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/model/ListModel.h>
#include <fastdds_monitor/model/SubListedListItem.h>

namespace models {

/**
 * Abstract class that encapsulate the behaviour of a Model that contains Entities in the form
 * of \c SubListedListModel , that means that items in this model has submodels.
 */
class SubListedListModel : public ListModel
{
    Q_OBJECT

public:

    /**
     * Constructor.
     */
    explicit SubListedListModel(
            SubListedListItem* prototype,
            QObject* parent = 0);

    /**
     * Returns the model contained by row item identified by a given item id.
     */
    Q_INVOKABLE QObject* subModelFromEntityId(
            QString entity_id);
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_SUBLISTEDLISTMODEL_H
