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
 * @file TopicModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_LOGICAL_TOPICMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_LOGICAL_TOPICMODELITEM_H

#include <fastdds_monitor/model/ListItem.h>

namespace models {


/**
 * @brief Class that represents an Topic Item in the Logical Model
 */
class TopicModelItem : public ListItem
{
    Q_OBJECT

public:

    //! Add new roles only for Topic items
    enum TopicModelItemRoles
    {
        typeRole = ModelItemRoles::nameRole + 1,    //! Role for attribute Type
    };

    //! Default ListItem constructor
    using ListItem::ListItem;

    //! Override the ListItem \c data method to add new roles
    QVariant data(
            int role) const override;

    //! Getter for type attribute
    QString type() const;

    //! Override the ListItem \c roleNames method to add new roles
    QHash<int, QByteArray> roleNames() const override;

    //! Overwriter entity kind
    virtual backend::EntityKind backend_kind() const override
    {
        return backend::EntityKind::TOPIC;
    }

};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_LOGICAL_TOPICMODELITEM_H
