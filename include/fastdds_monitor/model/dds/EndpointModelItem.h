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
