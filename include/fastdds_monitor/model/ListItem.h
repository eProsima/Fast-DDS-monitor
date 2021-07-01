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
 * @file ListItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_LISTITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_LISTITEM_H

#include <QObject>
#include <QVariant>
#include <QHash>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/backend/backend_utils.h>
#include <fastdds_monitor/model/model_types.h>

namespace models {

class ListModel;

/**
 * @brief Abstract class that encapsulate the behaviour of entity Items in a model
 *
 * Each Item represents a different \c Entity in the backend.
 *
 * Implement the constructors for every Item with a backend \c EntityId .
 * Implement main functions of every entity to retrieve internal data that is available in every entity kind,
 * that is id, name and their roles associated.
 */
class ListItem : public QObject
{
    Q_OBJECT

public:

    //! Role names to allow queries to get some specific information from the Item
    enum ModelItemRoles
    {
        idRole = Qt::UserRole + 1,      //! Role for attribute Id
        kindRole,                       //! Role for attribute Kind
        aliveRole,                      //! Role for attribute Alive
        nameRole                        //! Role for attribute Name
    };

    //! Default QObject constructor. Used for model specification
    ListItem(
            QObject* parent = 0);

    //! Default QObject constructor. Used for model specification
    ListItem(
            backend::EntityId id,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ListItem(
            backend::EntityId id,
            backend::EntityInfo info,
            QObject* parent = 0);

    //! ListItem destructor
    ~ListItem();

    /**
     * @brief Item id getter
     *
     * Retrieve the Item id, that is the backend entity id in QString format.
     *
     * @return backend entity id
     */
    virtual EntityId entity_id() const;

    /**
     * @brief Entity name getter
     *
     * This value is get with tag "name" in this item \c info
     *
     * @return entity name
     */
    virtual QString name() const;

    /**
     * @brief Entity info getter
     * @return entity info
     */
    virtual backend::EntityInfo info() const;

    /**
     * @brief Entity kind getter
     * @return entity kind in QString format
     */
    virtual QString kind() const;

    /**
     * @brief Entity kind backend type getter
     * @return entity kind
     */
    virtual backend::EntityKind backend_kind() const
    {
        return backend::EntityKind::INVALID;
    }

    /**
     * @brief Entity alive status getter
     * @return entity alive status
     */
    virtual bool alive() const;

    /**
     * @brief Item info setter
     *
     * Set the info to the Item.
     * This is used when constructing a new entity, avoiding to call the backend in Item construction.
     *
     * @warning This method do not modify the backend information
     *
     * @param info new info
     */
    void info(
            backend::EntityInfo info)
    {
        info_ = info;
    }

    /**
     * @brief Entity id getter
     *
     * Retrieve the backend id that reference to the entity encapsulated in this item.
     *
     * @return backend entity id
     */
    backend::EntityId get_entity_id() const;

    /**
     * @brief General getter to return every internal value
     *
     * This method allows to retrieve every internal Qt information from the Item.
     * This is needed for the QML method to print the entity information.
     *
     * In Abstract ListItem it allows to get the id and name of the entity.
     * Override this method in subclasses with different values in order to be able to access to all of them.
     *
     * @param role value of \c ModelItemRoles enumeration that references an internal value
     *
     * @return value of the role for this item
     */
    virtual QVariant data(
            int role) const;

    /**
     * @brief Roles getter
     *
     * Returns all the possible roles that are implemented for this object.
     * By this values, it is possible to get the internal data by calling \c data method.
     *
     * @return role names
     */
    virtual QHash<int, QByteArray> roleNames() const;

    /**
     * @brief Emit a signal that indicates that the Item has been modified
     */
    virtual void triggerItemUpdate()
    {
        emit dataChanged();
    }

signals:

    //! Communicate to the view that some internal info has been modified/added/removed/updated
    void dataChanged();

protected:

    //! Backend Id that references the \c Entity that this Item represents
    backend::EntityId id_;

    //! Backend info that contains all the needed information for this item
    backend::EntityInfo info_;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_LISTITEM_H
