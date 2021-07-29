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
 * @file EntityContainerModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_ENTITYCONTAINERMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_ENTITYCONTAINERMODELITEM_H

#include <QHash>
#include <QObject>
#include <QVariant>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/backend/backend_utils.h>
#include <fastdds_monitor/model/ListItem.h>
#include <fastdds_monitor/model/model_types.h>
#include <fastdds_monitor/model/SubListedListItem.h>
#include <fastdds_monitor/model/SubListedListModel.h>

namespace models {

/**
 * @brief Abstract class that encapsulate the behaviour of model items that have subentities
 *
 * This class implements the constructors for every Item that has subentities.
 *
 * This class is needed to create a template for different entities with subentities, as those subentities
 * could be single entities, or entities with subentities.
 * This template is not done in \c SubListedListItem class because that class may remain non template as
 * it must interact with QML code.
 *
 * @tparam SubEntityClass class of subentities. i.e. \c UserModelItem or \c LocatorModelItem
 * @tparam SubEntityModelClass kind of model that the subentities has: \c ListModel or \c SubListedListModel
 */
template<class SubEntityClass, class SubEntityModelClass>
class EntityContainerModelItem : public SubListedListItem
{
public:

    //! QObject defult constructor that creates the submodule by the template classes
    EntityContainerModelItem(
            QObject* parent = 0)
        : SubListedListItem(parent)
    {
        subentities_list_model_ = new SubEntityModelClass(new SubEntityClass());
    }

    //! Item constructor that creates the submodule by the template classes and get an \c EntityId reference to entity
    EntityContainerModelItem(
            backend::EntityId id,
            backend::EntityInfo info,
            QObject* parent = 0)
        : SubListedListItem(id, info, parent)
    {
        subentities_list_model_ = new SubEntityModelClass(new SubEntityClass());
    }

};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_ENTITYCONTAINERMODELITEM_H
