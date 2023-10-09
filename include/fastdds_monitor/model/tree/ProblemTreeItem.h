/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Maurizio Ingrassia
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_PROBLEMTREEITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_PROBLEMTREEITEM_H

#include <QVariant>
#include <fastdds_monitor/backend/backend_types.h>

namespace models {

/*!
 * This class represents a node of the ProblemTreeModel.
 * The items are meant to be managed from the ProblemTreeModel, thus is only allowed
 * to modify the stored data.
 * Parenting and deletion are dealt from the ProblemTreeModel. Deleting a ProblemTreeItem
 * will call the delete for each child node.
 */
class ProblemTreeItem
{
    friend class ProblemTreeModel;

public:
    //! Create an empty item.
    ProblemTreeItem();

    //! Create an item with the given data.
    explicit ProblemTreeItem(
            const QVariant& data);

    //! Create an item with the given data as string.
    explicit ProblemTreeItem(
            const backend::EntityId& id,
            const std::string& data);

    //! Create an item with the given data as string.
    explicit ProblemTreeItem(
            const backend::EntityId& id,
            const backend::StatusKind& kind,
            const std::string& data);

    //! Destroy the item. It will destroy every child.
    ~ProblemTreeItem();

    //! Return the stored data of the node.
    const QVariant& data() const;

    //! Set the internal data of the node.
    void setData(
            const QVariant& data);

    //! Return the number of children nodes.
    int childCount() const;

    int row() const;

    //! Return true if the node is a leaf node (no children).
    bool isLeaf() const;

    //! Return the depth of this node inside the tree.
    int depth() const;

    ProblemTreeItem* child(
            int row);

    backend::EntityId get_id();

    backend::StatusKind get_kind();

private:
    ProblemTreeItem* parentItem();

    void setParentItem(
            ProblemTreeItem* parentItem);

    void appendChild(
            ProblemTreeItem* item);

    void removeChild(
            ProblemTreeItem* item);

private:
    backend::EntityId _id;
    QVariant _itemData;
    ProblemTreeItem* _parentItem;
    QVector<ProblemTreeItem*> _childItems;
    backend::StatusKind _kind;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_PROBLEMTREEITEM_H
