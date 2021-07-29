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
 * @file TreeItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_TREEITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_TREEITEM_H

#include <QList>
#include <QVariant>

namespace models {

/**
 * @brief Abstract class that encapsulate the behaviour of an information Tree
 *
 * Tree Item is an information structure in tree format, where each node is a \c TreeItem .
 * Every node has its own information: QString value.
 * Every node can have non, one or multiple children that are of \c TreeItem class.
 *
 * These items are created from \c TreeModel object, that works as a \c TreeItem factory.
 */
class TreeItem
{
public:

    //! Values that are stored inside every TreeItem and can be accessed by \c data method
    enum TreeItemData
    {
        NAME,           //! Item Name
        VALUE           //! Item value
    };

    //! Constructor with reference to the father node and the data this node holds
    explicit TreeItem(
            const QList<QString>& data,
            TreeItem* parent_item = 0);

    //! Delete and release all the information of nodes below and itself
    ~TreeItem();

    //! Append a node child to this node
    void append_child(
            TreeItem* child);

    //! Return the child node in the position \c row
    TreeItem* child_item(
            int row);

    //! Count the number of children
    int child_count() const;

    //! Count the number of columns (in our case always 2: name & value)
    int column_count() const;

    //! Count the number of columns
    QVariant data(
            int column) const;

    //! Return the name of the node
    QVariant get_item_name() const;

    //! Return the value of the node
    QVariant get_item_value() const;

    //! Return the name of the node in string format
    QString name() const;

    //! Return the row that this node has regarding its parent
    int row() const;

    //! Return the parent reference
    TreeItem* parent_item();

    //! Clear all the nodes below
    void clear();

private:

    //! List of children nodes
    QList<TreeItem*> child_items_;

    //! List of data that this node holds
    QList<QString> item_data_;

    //! Reference to the father node
    TreeItem* parent_item_;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_TREEITEM_H
