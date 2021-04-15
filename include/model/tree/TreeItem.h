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
 * Tree Item is an information structure in tree format, where each node is a \c TreeItem
 * Every node has its own information: QString value
 * Every node can have non, one or multiple children that are of \c TreeItem class
 *
 * These items are created from \c TreeModel object, that works as a \c TreeItem factory
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
