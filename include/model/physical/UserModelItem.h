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
 * @file UserModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_PHYSICAL_USERMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_PHYSICAL_USERMODELITEM_H

#include <include/model/EntityContainerModelItem.h>
#include <include/model/physical/ProcessModelItem.h>

namespace models {

/**
 * @brief Class that represents a User Item in the Physical Model
 *
 * It is not needed to implement any extra method because User do not have extra fields of info
 * The Process subitems are already managed by \c EntityContainerModelItem class
 */
class UserModelItem : public EntityContainerModelItem<ProcessModelItem, ListModel>
{

public:

    // Use EntityContainerModelItem constructors
    using EntityContainerModelItem::EntityContainerModelItem;

};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_PHYSICAL_USERMODELITEM_H
