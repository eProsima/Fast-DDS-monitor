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

    //! Create an Entity item / top level item
    explicit ProblemTreeItem(
            const backend::EntityId& id,
            const std::string& name,
            const bool& is_error,
            const std::string& description);

    //! Create an item with the problem parameters
    explicit ProblemTreeItem(
            const backend::EntityId& id,
            const backend::StatusKind& kind,
            const std::string& name,
            const bool& is_error,
            const std::string& value,
            const std::string& description);

    //! Destroy the item. It will destroy every child.
    ~ProblemTreeItem();

    //! Return the stored data of the node.
    const QVariant& data() const;

    //! Return the stored data of the node.
    const QVariant& data(
            int role) const;

    const QVariant& entity_id() const;

    const QVariant& status_kind() const;

    const QVariant& name() const;

    const QVariant& status() const;

    const QVariant& value() const;

    const QVariant& description() const;

    const QVariant& alive() const;

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

    backend::EntityId id();

    backend::StatusKind kind();

    bool is_error();

    void is_error(
            bool val);

    std::string name_str();

    std::string value_str();

    std::string description_str();

    //! Increases the issues counter of a top level entity item
    int recalculate_entity_counter();

private:
    ProblemTreeItem* parentItem();

    void setParentItem(
            ProblemTreeItem* parentItem);

    void appendChild(
            ProblemTreeItem* item);

    void removeChild(
            ProblemTreeItem* item);

private:
    ProblemTreeItem* parent_item_;
    QVector<ProblemTreeItem*> child_items_;
    backend::EntityId id_;
    backend::StatusKind kind_;
    std::string name_;
    bool is_status_error_;
    std::string value_;
    std::string description_;
    bool is_active_;
    QVariant id_variant_;
    QVariant kind_variant_;
    QVariant name_variant_;
    QVariant is_status_error_variant_;
    QVariant value_variant_;
    QVariant description_variant_;
    QVariant is_active_variant_;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_PROBLEMTREEITEM_H
