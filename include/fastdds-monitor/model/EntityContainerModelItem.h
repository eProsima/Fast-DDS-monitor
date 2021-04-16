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
 * @file EntityContainerModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_ENTITYCONTAINERMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_ENTITYCONTAINERMODELITEM_H

#include <QHash>
#include <QObject>
#include <QVariant>

#include <fastdds-monitor/backend/backend_types.h>
#include <fastdds-monitor/backend/backend_utils.h>
#include <fastdds-monitor/model/ListItem.h>
#include <fastdds-monitor/model/model_types.h>
#include <fastdds-monitor/model/SubListedListItem.h>
#include <fastdds-monitor/model/SubListedListModel.h>

namespace models
{

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
public :

    //! QObject defult constructor that creates the submodule by the template classes
    EntityContainerModelItem(
            QObject *parent = 0)
        : SubListedListItem(parent)
    {
        subentities_list_model_ = new SubEntityModelClass(new SubEntityClass());
    }

    //! Item constructor that creates the submodule by the template classes and get an \c EntityId reference to entity
    EntityContainerModelItem(
            backend::EntityId id,
            QObject* parent = 0)
        : SubListedListItem(id, parent)
    {
        subentities_list_model_ = new SubEntityModelClass(new SubEntityClass());
    }

};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_ENTITYCONTAINERMODELITEM_H
