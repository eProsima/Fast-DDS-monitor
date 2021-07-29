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
