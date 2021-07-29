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
 * @file LocatorModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_DDS_LOCATORMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_DDS_LOCATORMODELITEM_H

#include <fastdds_monitor/model/ListItem.h>

namespace models {

/**
 * @brief Class that represents a Locator Item in the DDS Model
 */
class LocatorModelItem : public ListItem
{
    Q_OBJECT

public:

    // Use ListItem constructors
    using ListItem::ListItem;

    //! Overwriter entity kind
    virtual backend::EntityKind backend_kind() const override
    {
        return backend::EntityKind::LOCATOR;
    }

};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_DDS_LOCATORMODELITEM_H
