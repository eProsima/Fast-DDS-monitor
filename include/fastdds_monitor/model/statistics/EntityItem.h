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

    //! Default ListItem constructor
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
