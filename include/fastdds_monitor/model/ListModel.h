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
 * @file ListModel.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_LISTMODEL_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_LISTMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QList>
#include <QtAlgorithms>
#include <QVariant>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/model/ListItem.h>

namespace models {

/**
 * @brief Abstract class that encapsulate the behaviour of a Model that contains Entities in the form of Items
 *
 * The \c ListModel contains a serie of \c ListItem , which each of them represents a backend \c Entity .
 * It implements the main methods to interact with the view.
 *
 * These models are the graphic representation for the backed Entities, storing internally the items that represent
 * each Entity, its information and their subentities in the form of other models.
 * They also manage the interaction between the view, the controller and the items.
 */
class ListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:

    /**
     * Constructor.
     */
    explicit ListModel(
            ListItem* prototype,
            QObject* parent = 0);

    /**
     * Destructor.
     */
    ~ListModel();

    /**
     * Returns the number of rows under the given parent.
     * When the parent is valid it means that rowCount is returning the number of children of parent.
     */
    int rowCount(
            const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

    /**
     * Returns the data stored under the given role for the item referred to by the index.
     */
    QVariant data(
            const QModelIndex& index,
            int role) const Q_DECL_OVERRIDE;

    /**
     * Returns the model's role names.
     */
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    /**
     * This function provides a convenient way to append a single new item.
     */
    void appendRow(
            ListItem* item);

    /**
     * Appends several items to the Model.
     */
    void appendRows(
            QList<ListItem*>& items);

    /**
     * Inserts a single row before the given row in the child items of the parent specified.
     */
    void insertRow(
            int row,
            ListItem* item);

    /**
     * Removes a single row at the position given by row.
     * Returns true if the row was removed, and false if the row was not found or is not valid.
     */
    bool removeRow(
            int row,
            const QModelIndex& index = QModelIndex());

    /**
     * Removes several rows starting at position given by row until either count or the model's last row is reached.
     * Returns true if the rows were removed, false if the given initial row was not fount or is not invalid.
     */
    bool removeRows(
            int row,
            int count,
            const QModelIndex& index = QModelIndex()) Q_DECL_OVERRIDE;

    /**
     * Returns the item whose id matches the models itemId.
     */
    ListItem* find(
            EntityId itemId) const;

    /**
     * Returns the item whose id matches the backend itemId.
     *
     * @note This method is faster with backend than models id as the actual value stored is \c backend::EntityId
     */
    ListItem* find(
            backend::EntityId itemId) const;

    /**
     * Returns the item whose id matches the itemId.
     */
    ListItem* at(
            int index) const;

    /**
     * Returns the row index of item in the model.
     */
    int getRowFromItem(
            ListItem* item) const;

    /**
     * Returns the index of the row in the model containing the item.
     */
    QModelIndex indexFromItem(
            ListItem* item) const;

    /**
     * Returns a QList containing the items of the model.
     */
    QList<ListItem*> to_QList() const;

    /**
     * Returns a QVariant containg the data of the row item at a given index in the model.
     */
    Q_INVOKABLE QVariant get(
            int index);

    /**
     * Returns the row index of an item given the models item id.
     */
    Q_INVOKABLE int rowIndexFromId(
            EntityId itemId);

    /**
     * Returns the row index of an item given the backend item id.
     */
    Q_INVOKABLE int rowIndexFromId(
            backend::EntityId itemId);

    /**
     * Clears the whole model removing all rows.
     */
    Q_INVOKABLE void clear();

protected:

    //! Void ListItem that is used to know the role names. This is why a default constructor is needed in \c ListItem
    ListItem* prototype_;

    // This object stores the subitems indexing by <index> (internal list index) that is used by qt.
    // Thus, it is not easy to create a map with item and entity in a simple way.
    //! List of Items under this model
    QList<ListItem*> items_;

private slots:

    /**
     * Slot triggered when a row item needs to be updated to reflect data changes.
     */
    void updateItem();

signals:

    //! Signal that communicates to the view that the number of items has changed
    void countChanged(
            int count);
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_LISTMODEL_H
