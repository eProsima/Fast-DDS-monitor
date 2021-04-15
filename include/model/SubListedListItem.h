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
 * @file SubListedListItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_SUBLISTEDLISTITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_SUBLISTEDLISTITEM_H

#include <include/backend/backend_types.h>
#include <include/model/ListItem.h>
#include <include/model/ListModel.h>

namespace models {

/**
 * @brief Abstract class that encapsulate the behaviour of entity Items that contains subentities
 *
 * Each Item represents a different \c Entity in the backend that has subentities
 *
 * Implement the constructors for every Item with a backend \c EntityId
 * Implement the functionality to manage the submodels and subitems
 */
class SubListedListItem : public ListItem
{
    Q_OBJECT

public:

    //! Default QObject constructor. Used for model specification
    SubListedListItem(
            QObject *parent = 0)
        : ListItem(parent)
    {
    }

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    SubListedListItem(
            backend::EntityId id,
            QObject* parent = 0)
        : ListItem(id, parent)
    {
    }

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
