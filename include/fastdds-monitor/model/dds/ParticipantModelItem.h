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
 * @file ParticipantModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_DDS_PARTICIPANTMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_DDS_PARTICIPANTMODELITEM_H

#include <fastdds-monitor/model/dds/EndpointModelItem.h>
#include <fastdds-monitor/model/EntityContainerModelItem.h>
#include <fastdds-monitor/model/SubListedListItem.h>

namespace models {

/**
 * @brief Class that represents a Participant Item in the DDS Model
 *
 * Each participant has subitems that represent the endpoints associated with it indistinctly if they
 * are datawriters or datareaders.
 */
class ParticipantModelItem : public EntityContainerModelItem<EndpointModelItem, SubListedListModel>
{
    Q_OBJECT

public:

    //! Add new roles only for Participant items
    enum ParticipantModelItemRoles
    {
        guidRole = ModelItemRoles::nameRole + 1,    //! Role for attribute GUID
        domainRole                                  //! Role for attribute Domain
    };

    //! Default QObject constructor. Used for model specification
    ParticipantModelItem(
            QObject* parent = 0)
        : EntityContainerModelItem(parent)
    {
    }

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ParticipantModelItem(
            backend::EntityId id,
            QObject* parent = 0)
        : EntityContainerModelItem(id, parent)
    {
    }

    //! Override the ListItem \c data method to add new roles
    QVariant data(
            int role) const override;

    //! Getter for guid attribute
    QString guid() const;

    //! Getter for domain attribute
    QString domain() const;

    //! Override the ListItem \c roleNames method to add new roles
    QHash<int, QByteArray> roleNames() const override;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_DDS_PARTICIPANTMODELITEM_H
