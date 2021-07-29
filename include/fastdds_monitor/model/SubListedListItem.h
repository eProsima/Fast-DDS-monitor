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
 * @file SubListedListItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_SUBLISTEDLISTITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_SUBLISTEDLISTITEM_H

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/model/ListItem.h>
#include <fastdds_monitor/model/ListModel.h>

namespace models {

/**
 * @brief Abstract class that encapsulate the behaviour of entity Items that contains subentities
 *
 * Each Item represents a different \c Entity in the backend that has subentities.
 *
 * Implement the constructors for every Item with a backend \c EntityId .
 * Implement the functionality to manage the submodels and subitems.
 */
class SubListedListItem : public ListItem
{
    Q_OBJECT

public:

    //! Default ListItem constructor
    using ListItem::ListItem;

    //! Clear and delete the subentities
    ~SubListedListItem()
    {
        if (subentities_list_model_)
        {
            subentities_list_model_->clear();
            delete subentities_list_model_;
        }
    }

    //! Return the submodel that contains the subentities of this item
    ListModel* submodel()  const
    {
        return subentities_list_model_;
    }

protected:

    //! Submodule with subentities
    ListModel* subentities_list_model_;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_SUBLISTEDLISTITEM_H
