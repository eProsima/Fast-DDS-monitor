// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
 * @file EntityProblemModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_STATUS_ENTITYPROBLEMMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_STATUS_ENTITYPROBLEMMODELITEM_H

#include <fastdds_monitor/model/status/EntityProblemContainerModelItem.h>
#include <fastdds_monitor/model/status/ProblemListModel.h>
#include <fastdds_monitor/model/status/ProblemModelItem.h>

namespace models {

/**
 * @brief Class that represents a Entity Problem Item in the Problem Model
 *
 * It is not needed to implement any extra method because domain do not have extra fields of info.
 * The Topic subitems are already managed by \c EntityContainerModelItem class.
 */
class EntityProblemModelItem : public EntityProblemContainerModelItem<ProblemModelItem, ProblemListModel>
{

public:

    // Use EntityProblemContainerModelItem constructors
    using EntityProblemContainerModelItem::EntityProblemContainerModelItem;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_STATUS_ENTITYPROBLEMMODELITEM_H
