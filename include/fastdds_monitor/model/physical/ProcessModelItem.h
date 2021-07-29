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
 * @file ProcessModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_PHYSICAL_PROCESSMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_PHYSICAL_PROCESSMODELITEM_H

#include <fastdds_monitor/model/ListItem.h>

namespace models {


/**
 * @brief Class that represents an Process Item in the DDS Model
 */
class ProcessModelItem : public ListItem
{
    Q_OBJECT

public:

    //! Add new roles only for Process items
    enum ProcessModelItemRoles
    {
        pidRole = ModelItemRoles::nameRole + 1, //! Role for attribute PID
    };


    //! Default ListItem constructor
    using ListItem::ListItem;

    //! Override the ListItem \c data method to add new roles
    QVariant data(
            int role) const override;

    //! Getter for pid attribute
    QString pid() const;

    //! Override the ListItem \c roleNames method to add new roles
    QHash<int, QByteArray> roleNames() const override;

    //! Overwriter entity kind
    virtual backend::EntityKind backend_kind() const override
    {
        return backend::EntityKind::PROCESS;
    }

};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_PHYSICAL_PROCESSMODELITEM_H
