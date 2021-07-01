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
 * @file HostModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_PHYSICAL_HOSTMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_PHYSICAL_HOSTMODELITEM_H

#include <fastdds_monitor/model/EntityContainerModelItem.h>
#include <fastdds_monitor/model/physical/UserModelItem.h>
#include <fastdds_monitor/model/SubListedListItem.h>

namespace models {


/**
 * @brief Class that represents a Host Item in the Physical Model
 *
 * It is not needed to implement any extra method because Host do not have extra fields of info.
 * The User subitems are already managed by \c EntityContainerModelItem class.
 */
class HostModelItem : public EntityContainerModelItem<UserModelItem, SubListedListModel>
{

public:

    // Use EntityContainerModelItem constructors
    using EntityContainerModelItem::EntityContainerModelItem;

    //! Overwriter entity kind
    virtual backend::EntityKind backend_kind() const override
    {
        return backend::EntityKind::HOST;
    }

};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_PHYSICAL_HOSTMODELITEM_H
