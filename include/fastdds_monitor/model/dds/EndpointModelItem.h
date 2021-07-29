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
 * @file EndpointModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_DDS_ENDPOINTMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_DDS_ENDPOINTMODELITEM_H

#include <fastdds_monitor/model/dds/LocatorModelItem.h>
#include <fastdds_monitor/model/EntityContainerModelItem.h>
#include <fastdds_monitor/model/ListItem.h>

namespace models {

/**
 * @brief Class that represents an Endpoint Item in the DDS Model
 *
 * Endpoint Item represents inditinctly a DataWriter or DataReader.
 * Each endpoint has subitems that represent the locators associated with it.
 */
class EndpointModelItem : public EntityContainerModelItem<LocatorModelItem, ListModel>
{
    Q_OBJECT

public:

    //! Add new roles only for Endpoint items
    enum EndpointModelItemRoles
    {
        guidRole = ModelItemRoles::nameRole + 1,    //! Role for attribute GUID
        topicRole                                   //! Role for attribute Topic
    };

    // EntityContainerModelItem default constructor
    EndpointModelItem(
            QObject* parent = 0)
        : EntityContainerModelItem(parent)
    {
    }

    // EntityContainerModelItem constructor
    EndpointModelItem(
            backend::EntityId id,
            backend::EntityInfo info,
            QObject* parent = 0)
        : EntityContainerModelItem(id, info, parent)
    {
    }

    //! Specific DDS Item constructor, with a backend \c EntityId associated
    EndpointModelItem(
            backend::EntityId id,
            backend::EntityInfo info,
            backend::EntityKind kind,
            QObject* parent = 0)
        : EntityContainerModelItem(id, info, parent)
        , kind_(kind)
    {
    }

    //! Override the ListItem \c data method to add new roles
    QVariant data(
            int role) const override;

    //! Getter for guid attribute
    QString guid() const;

    //! Getter for topic attribute
    QString topic() const;

    //! Override the ListItem \c roleNames method to add new roles
    QHash<int, QByteArray> roleNames() const override;

    //! Overwriter entity kind
    virtual backend::EntityKind backend_kind() const override
    {
        return kind_;
    }

protected:

    //! Wether the entity is DataWriter or DataReader
    backend::EntityKind kind_;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_DDS_ENDPOINTMODELITEM_H
