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

#include <iostream>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/backend/backend_utils.h>
#include <fastdds_monitor/model/tree/ProblemTreeItem.h>

namespace models {

ProblemTreeItem::ProblemTreeItem()
    : _id(backend::ID_ALL)
    , _itemData()
    , _parentItem(nullptr)
    , _kind(backend::StatusKind::INVALID)
{
}

ProblemTreeItem::ProblemTreeItem(
        const QVariant& data)
    : _id(backend::ID_ALL)
    , _itemData(data)
    , _parentItem(nullptr)
    , _kind(backend::StatusKind::INVALID)
{
}

ProblemTreeItem::ProblemTreeItem(
        const backend::EntityId& id,
        const std::string& data)
    : _id(id)
    , _itemData(QString::fromStdString(data))
    , _parentItem(nullptr)
    , _kind(backend::StatusKind::INVALID)
{
}

ProblemTreeItem::ProblemTreeItem(
        const backend::EntityId& id,
        const backend::StatusKind& kind,
        const std::string& data)
    : _id(id)
    , _itemData(QString::fromStdString(data))
    , _parentItem(nullptr)
    , _kind(kind)
{
}

ProblemTreeItem::~ProblemTreeItem()
{
    qDeleteAll(_childItems);
}

ProblemTreeItem* ProblemTreeItem::parentItem()
{
    return _parentItem;
}

void ProblemTreeItem::setParentItem(
        ProblemTreeItem* parentItem)
{
    _parentItem = parentItem;
}

void ProblemTreeItem::appendChild(
        ProblemTreeItem* item)
{
    if (item && !_childItems.contains(item))
    {
        _childItems.append(item);
    }
}

void ProblemTreeItem::removeChild(
        ProblemTreeItem* item)
{
    if (item)
    {
        _childItems.removeAll(item);
    }
}

ProblemTreeItem* ProblemTreeItem::child(
        int row)
{
    return _childItems.value(row);
}

int ProblemTreeItem::childCount() const
{
    return _childItems.count();
}

const QVariant& ProblemTreeItem::data() const
{
    return _itemData;
}

void ProblemTreeItem::setData(
        const QVariant& data)
{
    _itemData = data;
}

bool ProblemTreeItem::isLeaf() const
{
    return _childItems.isEmpty();
}

int ProblemTreeItem::depth() const
{
    int depth = 0;
    ProblemTreeItem* anchestor = _parentItem;
    while (anchestor)
    {
        ++depth;
        anchestor = anchestor->parentItem();
    }

    return depth;
}

int ProblemTreeItem::row() const
{
    if (_parentItem)
    {
        return _parentItem->_childItems.indexOf(const_cast<ProblemTreeItem*>(this));
    }

    return 0;
}

backend::EntityId ProblemTreeItem::get_id()
{
    return _id;
}

backend::StatusKind ProblemTreeItem::get_kind()
{
    return _kind;
}

} // namespace models
