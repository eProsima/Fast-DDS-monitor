// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima DDS Monitor.
//
// eProsima DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

/**
 * @file UserModelItem.hpp
 */

#ifndef _EPROSIMA_DDS_MONITOR_MODEL_PHYSICAL_USERMODELITEM_H
#define _EPROSIMA_DDS_MONITOR_MODEL_PHYSICAL_USERMODELITEM_H

#include <dds_monitor/model/EntityContainerModelItem.h>
#include <dds_monitor/model/physical/ProcessModelItem.h>

namespace models {

/**
 * @brief Class that represents a User Item in the Physical Model
 *
 * It is not needed to implement any extra method because User do not have extra fields of info.
 * The Process subitems are already managed by \c EntityContainerModelItem class.
 */
class UserModelItem : public EntityContainerModelItem<ProcessModelItem, ListModel>
{

public:

    // Use EntityContainerModelItem constructors
    using EntityContainerModelItem::EntityContainerModelItem;

    //! Overwriter entity kind
    virtual backend::EntityKind backend_kind() const override
    {
        return backend::EntityKind::USER;
    }

};

} // namespace models

#endif // _EPROSIMA_DDS_MONITOR_MODEL_PHYSICAL_USERMODELITEM_H
