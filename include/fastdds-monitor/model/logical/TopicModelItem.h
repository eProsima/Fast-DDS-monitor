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
 * @file TopicModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_LOGICAL_TOPICMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_LOGICAL_TOPICMODELITEM_H

#include <fastdds-monitor/model/ListItem.h>

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

    //! Default QObject constructor. Used for model specification
    TopicModelItem(
            QObject* parent = 0)
        : ListItem(parent)
    {
    }

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    TopicModelItem(
            backend::EntityId id,
            QObject* parent = 0)
        : ListItem(id, parent)
    {
    }

    //! Override the ListItem \c data method to add new roles
    QVariant data(
            int role) const override;

    //! Getter for type attribute
    QString type() const;

    //! Override the ListItem \c roleNames method to add new roles
    QHash<int, QByteArray> roleNames() const override;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_LOGICAL_TOPICMODELITEM_H
