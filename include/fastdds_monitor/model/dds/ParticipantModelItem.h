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
 * @file ParticipantModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_DDS_PARTICIPANTMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_DDS_PARTICIPANTMODELITEM_H

#include <fastdds_monitor/model/dds/EndpointModelItem.h>
#include <fastdds_monitor/model/EntityContainerModelItem.h>
#include <fastdds_monitor/model/SubListedListItem.h>

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

    //! Default ListItem constructor
    using EntityContainerModelItem::EntityContainerModelItem;

    //! Override the ListItem \c data method to add new roles
    QVariant data(
            int role) const override;

    //! Getter for guid attribute
    QString guid() const;

    //! Getter for domain attribute
    QString domain() const;

    //! Override the ListItem \c roleNames method to add new roles
    QHash<int, QByteArray> roleNames() const override;

    //! Overwriter entity kind
    virtual backend::EntityKind backend_kind() const override
    {
        return backend::EntityKind::PARTICIPANT;
    }

};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_DDS_PARTICIPANTMODELITEM_H
