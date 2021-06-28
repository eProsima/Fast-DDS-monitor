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
 * @file EntityItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_ENTITYITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_ENTITYITEM_H

#include <fastdds_monitor/model/ListItem.h>

namespace models {

/**
 * @brief Class that represents an Entity in the chart dialog
 */
class EntityItem : public ListItem
{
    Q_OBJECT

public:

    //! Add new roles only for Topic items
    enum EntityItemRoles
    {
        nameIdRole = ModelItemRoles::nameRole + 1,    //! Role for attribute Type
    };

    //!
    EntityItem(
            QObject* parent = 0)
        : ListItem(parent)
    {
    }

    //! Default QObject constructor. Used for model specification
    EntityItem(
            backend::EntityId id,
            backend::EntityKind kind,
            backend::EntityInfo info,
            QObject* parent = 0)
        : ListItem(id, info, parent)
        , kind_(kind)
    {
    }

    //! Override the ListItem \c data method to add new roles
    QVariant data(
            int role) const override;

    //! Getter for nameId attribute
    QString nameId() const;

    //! Override the ListItem \c roleNames method to add new roles
    QHash<int, QByteArray> roleNames() const override;

    //! Overwrite entity kind
    virtual backend::EntityKind backend_kind() const override
    {
        return kind_;
    }

protected:

    //! Backend Kind of the entity
    backend::EntityInfo kind_;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_ENTITYITEM_H
