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

#include <fastdds_monitor/model/tree/ProblemTreeModel.h>

#include <iostream>

#include <fastdds_monitor/backend/backend_utils.h>

namespace models {

ProblemTreeModel::ProblemTreeModel(
        QObject* parent)
    : QAbstractItemModel(parent)
    , _rootItem{ new ProblemTreeItem() }
    , _is_empty(false)
{
}

ProblemTreeModel::~ProblemTreeModel()
{
    delete _rootItem;
}

int ProblemTreeModel::rowCount(
        const QModelIndex& parent) const
{
    if (!parent.isValid())
    {
        return _rootItem->childCount();
    }

    return internalPointer(parent)->childCount();
}

int ProblemTreeModel::columnCount(
        const QModelIndex& /*parent*/) const
{
    // This is basically flatten as a list model
    return 1;
}

QModelIndex ProblemTreeModel::index(
        const int row,
        const int column,
        const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return {};
    }

    ProblemTreeItem* item = _rootItem;
    if (parent.isValid())
    {
        item = internalPointer(parent);
    }

    if (auto child = item->child(row))
    {
        return createIndex(row, column, child);
    }

    return {};
}

QModelIndex ProblemTreeModel::parent(
        const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return {};
    }

    ProblemTreeItem* childItem = internalPointer(index);
    ProblemTreeItem* parentItem = childItem->parentItem();

    if (!parentItem)
    {
        return {};
    }

    if (parentItem == _rootItem)
    {
        return {};
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

QVariant ProblemTreeModel::data(
        const QModelIndex& index,
        const int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return QVariant();
    }

    return internalPointer(index)->data();
}

bool ProblemTreeModel::setData(
        const QModelIndex& index,
        const QVariant& value,
        int /*role*/)
{
    if (!index.isValid())
    {
        return false;
    }

    if (auto item = internalPointer(index))
    {
        item->setData(value);
        emit dataChanged(index, index, {Qt::EditRole});
    }

    return false;
}

void ProblemTreeModel::addTopLevelItem(
        ProblemTreeItem* child)
{
    if (child)
    {
        addItem(_rootItem, child);
        if (child->get_id() == backend::ID_ALL &&_rootItem->childCount() == 1)
        {
            _is_empty = true;
        }
    }
}

void ProblemTreeModel::addItem(
        ProblemTreeItem* parent,
        ProblemTreeItem* child)
{
    if (!child || !parent)
    {
        return;
    }


    // if parent is topLevelItem (entity item)
    if (parent->get_id() != backend::ID_ALL && parent->get_kind() == backend::StatusKind::INVALID)
    {
        // For each problem in the entity item
        for (int i=0; i<parent->childCount(); i++)
        {
            // if overriding problem, remove previous problem
            if (parent->child(i)->get_id() == child->get_id() && parent->child(i)->get_kind() == child->get_kind())
            {
                emit layoutAboutToBeChanged();
                beginRemoveRows(QModelIndex(), qMax(parent->childCount() - 1, 0), qMax(parent->childCount(), 0));
                parent->removeChild(parent->child(i));
                endRemoveRows();
                emit layoutChanged();
            }
        }
    }

    emit layoutAboutToBeChanged();

    // remove possible parent from new child
    if (child->parentItem())
    {
        beginRemoveRows(QModelIndex(), qMax(parent->childCount() - 1, 0), qMax(parent->childCount(), 0));
        child->parentItem()->removeChild(child);
        endRemoveRows();
    }

    beginInsertRows(QModelIndex(), qMax(parent->childCount() - 1, 0), qMax(parent->childCount() - 1, 0));
    // set new parent in the child
    child->setParentItem(parent);
    // append child in parent's child list
    parent->appendChild(child);
    endInsertRows();

    emit layoutChanged();
}

void ProblemTreeModel::removeItem(
        ProblemTreeItem* item)
{
    if (!item)
    {
        return;
    }

    emit layoutAboutToBeChanged();

    if (item->parentItem())
    {
        beginRemoveRows(QModelIndex(), qMax(item->childCount() - 1, 0), qMax(item->childCount(), 0));
        item->parentItem()->removeChild(item);
        endRemoveRows();
    }

    emit layoutChanged();
}

ProblemTreeItem* ProblemTreeModel::rootItem() const
{
    return _rootItem;
}

QModelIndex ProblemTreeModel::rootIndex()
{
    return {};
}

int ProblemTreeModel::depth(
        const QModelIndex& index) const
{
    int count = 0;
    auto anchestor = index;
    if (!index.isValid())
    {
        return 0;
    }
    while (anchestor.parent().isValid())
    {
        anchestor = anchestor.parent();
        ++count;
    }

    return count;
}

void ProblemTreeModel::clear()
{
    emit layoutAboutToBeChanged();
    beginResetModel();
    delete _rootItem;
    _rootItem = new ProblemTreeItem();
    endResetModel();
    emit layoutChanged();
}

ProblemTreeItem* ProblemTreeModel::internalPointer(
        const QModelIndex& index) const
{
    return static_cast<ProblemTreeItem*>(index.internalPointer());
}

bool ProblemTreeModel::containsTopLevelItem(
        ProblemTreeItem* child)
{
    if (child)
    {
        return contains(_rootItem, child);
    }
    return false;
}

bool ProblemTreeModel::contains(
    ProblemTreeItem* parent,
    ProblemTreeItem* child)
{
    if (!parent || !child)
    {
        return false;
    }

    for (int i = 0; i < parent->childCount(); i++)
    {
        if (parent->child(i)->get_id() == child->get_id())
        {
            return true;
        }
    }
    return false;
}

bool ProblemTreeModel::is_empty()
{
    return _is_empty;
}

void ProblemTreeModel::removeEmptyItem()
{
    emit layoutAboutToBeChanged();
    for (int i=0; i<_rootItem->childCount(); i++)
    {
        if (_rootItem->child(i)->get_id() == backend::ID_ALL)
        {
            _rootItem->removeChild(_rootItem->child(i));
            _is_empty = false;
            break;
        }
    }
    emit layoutChanged();
}

ProblemTreeItem*  ProblemTreeModel::getTopLevelItem(
        const backend::EntityId& id,
        const std::string& data)
{
    // For each entity item in the three (root)
    for (int i=0; i<_rootItem->childCount(); i++)
    {
        // if exists
        if (_rootItem->child(i)->get_id() == id)
        {
            return _rootItem->child(i);
        }
    }

    // if not existing, create new topLevelItem
    ProblemTreeItem* new_entity_item = new ProblemTreeItem(id, data);
    addTopLevelItem(new_entity_item);
    return new_entity_item;
}

} // namespace models
