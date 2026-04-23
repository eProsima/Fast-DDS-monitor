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
 * @file DomainModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_LOGICAL_DOMAINMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_LOGICAL_DOMAINMODELITEM_H

#include <fastdds_monitor/model/EntityContainerModelItem.h>
#include <fastdds_monitor/model/ListModel.h>
#include <fastdds_monitor/model/logical/TopicModelItem.h>

namespace models {

/**
 * @brief Class that represents a Domain Item in the Logic Model
 *
 * It is not needed to implement any extra method because domain do not have extra fields of info.
 * The Topic subitems are already managed by \c EntityContainerModelItem class.
 */
class DomainModelItem : public EntityContainerModelItem<TopicModelItem, ListModel>
{

public:

    // Use EntityContainerModelItem constructors
    using EntityContainerModelItem::EntityContainerModelItem;

    //! Overwriter entity kind
    virtual backend::EntityKind backend_kind() const override
    {
        return backend::EntityKind::DOMAIN_ENTITY;
    }

};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_LOGICAL_DOMAINMODELITEM_H
