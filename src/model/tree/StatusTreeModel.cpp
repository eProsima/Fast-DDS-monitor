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

#include <fastdds_monitor/model/tree/StatusTreeModel.h>

#include <iostream>
#include <QQmlEngine>

#include <fastdds_monitor/backend/backend_utils.h>

namespace models {

StatusTreeModel::StatusTreeModel(
        QObject* parent)
    : QAbstractItemModel(parent)
    , source_model_(nullptr)
    , root_item_{ new StatusTreeItem() }
    , is_empty_(false)
    , current_filter_(backend::ID_ALL)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

StatusTreeModel::~StatusTreeModel()
{
    delete root_item_;
}

void StatusTreeModel::set_source_model(
        StatusTreeModel* source_model)
{
    source_model_ = source_model;
    filter(current_filter_);
}

void StatusTreeModel::filter_proxy(
        const QVariant& entity_id)
{
    if (source_model_)
    {
        filter(entity_id.toInt());
    }
}

void StatusTreeModel::filter(
        const backend::EntityId entity_id)
{
    clear();
    if (current_filter_ != entity_id)
    {
        current_filter_ = entity_id;
    }
    if (source_model_)
    {
        for (int i = 0; i < source_model_->rootItem()->childCount(); i++)
        {
            addTopLevelItem(filtered_copy(source_model_->rootItem()->child(i), entity_id));
        }
    }
}

StatusTreeItem* StatusTreeModel::filtered_copy(
        StatusTreeItem* source,
        const backend::EntityId entity_id)
{
    // copy source data in destination data
    if (source->id() == entity_id || entity_id == backend::ID_ALL)
    {
        StatusTreeItem* destination = new StatusTreeItem(
            source->id(),
            source->kind(),
            source->name_str(),
            source->status_level(),
            source->value_str(),
            source->description_str());
        for (int i = 0; i < source->childCount(); i++)
        {
            addItem(destination, filtered_copy(source->child(i), entity_id));
        }
        return destination;
    }
    return nullptr;
}

int StatusTreeModel::rowCount(
        const QModelIndex& parent) const
{
    if (!parent.isValid())
    {
        return root_item_->childCount();
    }

    return internalPointer(parent)->childCount();
}

int StatusTreeModel::columnCount(
        const QModelIndex& /*parent*/) const
{
    // This is basically flatten as a list model
    return 1;
}

QModelIndex StatusTreeModel::index(
        const int row,
        const int column,
        const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return {};
    }

    StatusTreeItem* item = root_item_;
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

QModelIndex StatusTreeModel::parent(
        const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return {};
    }

    StatusTreeItem* childItem = internalPointer(index);
    StatusTreeItem* parentItem = childItem->parentItem();

    if (!parentItem)
    {
        return {};
    }

    if (parentItem == root_item_)
    {
        return {};
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

QVariant StatusTreeModel::data(
        const QModelIndex& index,
        const int role) const
{
    return name(index, role);
}

QVariant StatusTreeModel::name(
        const QModelIndex& index,
        const int /*role*/) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    return internalPointer(index)->name();
}

QVariant StatusTreeModel::id(
        const QModelIndex& index,
        const int /*role*/) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    return internalPointer(index)->entity_id();
}

QVariant StatusTreeModel::status(
        const QModelIndex& index,
        const int /*role*/) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    return internalPointer(index)->status();
}

QVariant StatusTreeModel::kind(
        const QModelIndex& index,
        const int /*role*/) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    return internalPointer(index)->status_kind();
}

QVariant StatusTreeModel::value(
        const QModelIndex& index,
        const int /*role*/) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    return internalPointer(index)->value();
}

QVariant StatusTreeModel::description(
        const QModelIndex& index,
        const int /*role*/) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    return internalPointer(index)->description();
}

QVariant StatusTreeModel::alive(
        const QModelIndex& index,
        const int /*role*/) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    return internalPointer(index)->alive();
}

bool StatusTreeModel::setData(
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

bool StatusTreeModel::removeRow(
        int /*row*/,
        const QModelIndex& index)
{
    if (!index.isValid())
    {
        return false;
    }

    if (auto item = internalPointer(index))
    {
        std::cout << "removing" << std::endl;
        removeItem(item);
        std::cout << "removed" << std::endl;
    }

    return false;
}

void StatusTreeModel::addTopLevelItem(
        StatusTreeItem* child)
{
    if (child)
    {
        addItem(root_item_, child);
        if (child->id() == backend::ID_ALL && root_item_->childCount() == 1)
        {
            is_empty_ = true;
        }
    }
}

void StatusTreeModel::addItem(
        StatusTreeItem* parent,
        StatusTreeItem* child)
{
    if (!child || !parent)
    {
        return;
    }


    // if parent is topLevelItem (entity item)
    if (parent->id() != backend::ID_ALL && parent->kind() == backend::StatusKind::INVALID)
    {
        // For each status in the entity item
        for (int i = 0; i < parent->childCount(); i++)
        {
            // if overriding status, remove previous status
            if (parent->child(i)->id() == child->id() && parent->child(i)->kind() == child->kind())
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

void StatusTreeModel::removeItem(
        StatusTreeItem* item)
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

StatusTreeItem* StatusTreeModel::rootItem() const
{
    return root_item_;
}

QModelIndex StatusTreeModel::rootIndex()
{
    return {};
}

int StatusTreeModel::depth(
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

void StatusTreeModel::clear()
{
    emit layoutAboutToBeChanged();
    beginResetModel();
    delete root_item_;
    root_item_ = new StatusTreeItem();
    endResetModel();
    emit layoutChanged();
}

StatusTreeItem* StatusTreeModel::internalPointer(
        const QModelIndex& index) const
{
    return static_cast<StatusTreeItem*>(index.internalPointer());
}

bool StatusTreeModel::containsTopLevelItem(
        StatusTreeItem* child)
{
    if (child)
    {
        return contains(root_item_, child);
    }
    return false;
}

bool StatusTreeModel::contains(
        StatusTreeItem* parent,
        StatusTreeItem* child)
{
    if (!parent || !child)
    {
        return false;
    }

    for (int i = 0; i < parent->childCount(); i++)
    {
        if (parent->child(i)->id() == child->id())
        {
            return true;
        }
    }
    return false;
}

StatusTreeItem* StatusTreeModel::child(
        int row)
{
    if (row >= 0 && row < root_item_->childCount())
    {
        return root_item_->child(row);
    }

    return nullptr;
}

bool StatusTreeModel::is_empty()
{
    return is_empty_;
}

void StatusTreeModel::removeEmptyItem()
{
    emit layoutAboutToBeChanged();
    for (int i = 0; i < root_item_->childCount(); i++)
    {
        if (root_item_->child(i)->id() == backend::ID_ALL)
        {
            root_item_->removeChild(root_item_->child(i));
            is_empty_ = false;
            break;
        }
    }
    emit layoutChanged();
}

StatusTreeItem*  StatusTreeModel::getTopLevelItem(
        const backend::EntityId& id,
        const std::string& data,
        const backend::StatusLevel& status,
        const std::string& description)
{
    // For each entity item in the three (root)
    for (int i = 0; i < root_item_->childCount(); i++)
    {
        // if exists
        if (root_item_->child(i)->id() == id)
        {
            return root_item_->child(i);
        }
    }

    // if not existing, create new topLevelItem
    StatusTreeItem* new_entity_item = new StatusTreeItem(id, data, status, description);
    addTopLevelItem(new_entity_item);
    return new_entity_item;
}

} // namespace models
