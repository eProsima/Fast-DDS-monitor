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
#include <QQmlEngine>

#include <fastdds_monitor/backend/backend_utils.h>

namespace models {

ProblemTreeModel::ProblemTreeModel(
        QObject* parent)
    : QAbstractItemModel(parent)
    , source_model_(nullptr)
    , root_item_{ new ProblemTreeItem() }
    , is_empty_(false)
    , current_filter_(backend::ID_ALL)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

ProblemTreeModel::~ProblemTreeModel()
{
    delete root_item_;
}

void ProblemTreeModel::set_source_model(
        ProblemTreeModel* source_model)
{
    source_model_ = source_model;
    filter(current_filter_);
}

void ProblemTreeModel::filter_proxy(
            const QVariant& entity_id)
{
    if (source_model_)
    {
        filter(entity_id.toInt());
    }
}

void ProblemTreeModel::filter(
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
            addTopLevelItem(copy(source_model_->rootItem()->child(i), entity_id));
        }
    }
}

ProblemTreeItem* ProblemTreeModel::copy(
        ProblemTreeItem* source,
        const backend::EntityId entity_id)
{
    // copy source data in destiny data
    if (source->id() == entity_id || entity_id == backend::ID_ALL)
    {
        ProblemTreeItem* destiny = new ProblemTreeItem(
                source->id(),
                source->kind(),
                source->name_str(),
                source->is_error(),
                source->value_str(),
                source->description_str());
        for (int i = 0; i < source->childCount(); i++)
        {
            addItem(destiny, copy(source->child(i), entity_id));
        }
        return destiny;
    }
    return nullptr;
}


int ProblemTreeModel::rowCount(
        const QModelIndex& parent) const
{
    if (!parent.isValid())
    {
        return root_item_->childCount();
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

    ProblemTreeItem* item = root_item_;
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

    if (parentItem == root_item_)
    {
        return {};
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

QVariant ProblemTreeModel::data(
        const QModelIndex& index,
        const int role) const
{
    if (!index.isValid()/* || role != Qt::DisplayRole*/)
    {
        return QVariant();
    }

    return internalPointer(index)->data(role);
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

bool ProblemTreeModel::removeRow(
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

void ProblemTreeModel::addTopLevelItem(
        ProblemTreeItem* child)
{
    if (child)
    {
        addItem(root_item_, child);
        if (child->id() == backend::ID_ALL &&root_item_->childCount() == 1)
        {
            is_empty_ = true;
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
    if (parent->id() != backend::ID_ALL && parent->kind() == backend::StatusKind::INVALID)
    {
        // For each problem in the entity item
        for (int i=0; i<parent->childCount(); i++)
        {
            // if overriding problem, remove previous problem
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
    return root_item_;
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
    delete root_item_;
    root_item_ = new ProblemTreeItem();
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
        return contains(root_item_, child);
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
        if (parent->child(i)->id() == child->id())
        {
            return true;
        }
    }
    return false;
}

ProblemTreeItem* ProblemTreeModel::child(
        int row)
{
    if (row >= 0 && row < root_item_->childCount())
    {
        return root_item_->child(row);
    }

    return nullptr;
}

bool ProblemTreeModel::is_empty()
{
    return is_empty_;
}

void ProblemTreeModel::removeEmptyItem()
{
    emit layoutAboutToBeChanged();
    for (int i=0; i<root_item_->childCount(); i++)
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

ProblemTreeItem*  ProblemTreeModel::getTopLevelItem(
        const backend::EntityId& id,
        const std::string& data,
        const bool& is_error,
        const std::string& description)
{
    // For each entity item in the three (root)
    for (int i=0; i<root_item_->childCount(); i++)
    {
        // if exists
        if (root_item_->child(i)->id() == id)
        {
            return root_item_->child(i);
        }
    }

    // if not existing, create new topLevelItem
    ProblemTreeItem* new_entity_item = new ProblemTreeItem(id, data, is_error, description);
    addTopLevelItem(new_entity_item);
    return new_entity_item;
}


QHash<int, QByteArray> ProblemTreeModel::roleNames() const
{
    // TODO Jesus this roles are not currently used in the QML, find out why
    QHash<int, QByteArray>  roles;

    roles[idRole] = "id";
    roles[statusRole] = "status";
    roles[kindRole] = "kind";
    roles[valueRole] = "value";
    roles[descriptionRole] = "description";
    roles[aliveRole] = "alive";
    roles[nameRole] = "name";

    return roles;
}

} // namespace models
