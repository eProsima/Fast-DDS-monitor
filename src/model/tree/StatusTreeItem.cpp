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
#include <fastdds_monitor/model/tree/StatusTreeItem.h>
#include <fastdds_monitor/model/tree/StatusTreeModel.h>

namespace models {

StatusTreeItem::StatusTreeItem()
    : parent_item_(nullptr)
    , id_(backend::ID_ALL)
    , kind_(backend::StatusKind::INVALID)
    , name_()
    , status_level_(backend::StatusLevel::OK_STATUS)
    , value_()
    , description_()
    , is_active_(true)
    , id_variant_(QVariant(backend::backend_id_to_models_id(id_)))
    , kind_variant_(QVariant(QString::fromStdString(backend::status_kind_to_string(kind_))))
    , name_variant_(QVariant())
    , status_level_variant_(QVariant(QString::fromStdString(backend::status_level_to_string(status_level_))))
    , value_variant_(QVariant())
    , description_variant_(QVariant())
    , is_active_variant_(QVariant(true))
{
}

StatusTreeItem::StatusTreeItem(
        const QVariant& data)
    : parent_item_(nullptr)
    , id_(backend::ID_ALL)
    , kind_(backend::StatusKind::INVALID)
    , name_(data.toString().toStdString())
    , status_level_(backend::StatusLevel::OK_STATUS)
    , value_()
    , description_()
    , is_active_(true)
    , id_variant_(QVariant(backend::backend_id_to_models_id(id_)))
    , kind_variant_(QVariant(QString::fromStdString(backend::status_kind_to_string(kind_))))
    , name_variant_(QVariant(QString::fromStdString(name_)))
    , status_level_variant_(QVariant(QString::fromStdString(backend::status_level_to_string(status_level_))))
    , value_variant_(QVariant())
    , description_variant_(QVariant())
    , is_active_variant_(QVariant(true))
{
}

StatusTreeItem::StatusTreeItem(
        const backend::EntityId& id,
        const std::string& name,
        const backend::StatusLevel& status_level,
        const std::string& description)
    : parent_item_(nullptr)
    , id_(id)
    , kind_(backend::StatusKind::INVALID)
    , name_(name)
    , status_level_(status_level)
    , value_()
    , description_(description)
    , is_active_(true)
    , id_variant_(QVariant(backend::backend_id_to_models_id(id_)))
    , kind_variant_(QVariant(QString::fromStdString(backend::status_kind_to_string(kind_))))
    , name_variant_(QVariant(QString::fromStdString(name)))
    , status_level_variant_(QVariant(QString::fromStdString(backend::status_level_to_string(status_level_))))
    , value_variant_(QVariant())
    , description_variant_(QVariant(QString::fromStdString(description)))
    , is_active_variant_(QVariant(true))
{
}

StatusTreeItem::StatusTreeItem(
        const backend::EntityId& id,
        const backend::StatusKind& kind,
        const std::string& name,
        const backend::StatusLevel& status_level,
        const std::string& value,
        const std::string& description)
    : parent_item_(nullptr)
    , id_(id)
    , kind_(kind)
    , name_(name)
    , status_level_(status_level)
    , value_(value)
    , description_(description)
    , is_active_(true)
    , id_variant_(QVariant(backend::backend_id_to_models_id(id_)))
    , kind_variant_(QVariant(QString::fromStdString(backend::status_kind_to_string(kind_))))
    , name_variant_(QVariant(QString::fromStdString(name_)))
    , status_level_variant_(QVariant(QString::fromStdString(backend::status_level_to_string(status_level_))))
    , value_variant_(QVariant(QString::fromStdString(value)))
    , description_variant_(QVariant(QString::fromStdString(description)))
    , is_active_variant_(QVariant(true))
{
}

StatusTreeItem::~StatusTreeItem()
{
    qDeleteAll(child_items_);
}

StatusTreeItem* StatusTreeItem::parentItem()
{
    return parent_item_;
}

void StatusTreeItem::setParentItem(
        StatusTreeItem* parentItem)
{
    parent_item_ = parentItem;
}

void StatusTreeItem::appendChild(
        StatusTreeItem* item)
{
    if (item && !child_items_.contains(item))
    {
        child_items_.append(item);
    }
}

void StatusTreeItem::removeChild(
        StatusTreeItem* item)
{
    if (item)
    {
        child_items_.removeAll(item);
        delete item;
    }
}

StatusTreeItem* StatusTreeItem::child(
        int row)
{
    return child_items_.value(row);
}

int StatusTreeItem::childCount() const
{
    return child_items_.count();
}

const QVariant& StatusTreeItem::entity_id() const
{
    return id_variant_;
}

const QVariant& StatusTreeItem::status_kind() const
{
    return kind_variant_;
}

const QVariant& StatusTreeItem::name() const
{
    return name_variant_;
}

const QVariant& StatusTreeItem::status() const
{
    return status_level_variant_;
}

const QVariant& StatusTreeItem::value() const
{
    return value_variant_;
}

const QVariant& StatusTreeItem::description() const
{
    return description_variant_;
}

const QVariant& StatusTreeItem::alive() const
{
    return is_active_variant_;
}

void StatusTreeItem::setData(
        const QVariant& data)
{
    name_variant_ = data;
}

bool StatusTreeItem::isLeaf() const
{
    return child_items_.isEmpty();
}

int StatusTreeItem::depth() const
{
    int depth = 0;
    StatusTreeItem* anchestor = parent_item_;
    while (anchestor)
    {
        ++depth;
        anchestor = anchestor->parentItem();
    }

    return depth;
}

int StatusTreeItem::row() const
{
    if (parent_item_)
    {
        return parent_item_->child_items_.indexOf(const_cast<StatusTreeItem*>(this));
    }

    return 0;
}

backend::EntityId StatusTreeItem::id()
{
    return id_;
}

backend::StatusKind StatusTreeItem::kind()
{
    return kind_;
}

backend::StatusLevel StatusTreeItem::status_level()
{
    return status_level_;
}

void StatusTreeItem::status_level(
        backend::StatusLevel val)
{
    status_level_ = val;
    status_level_variant_ = QVariant(QString::fromStdString(backend::status_level_to_string(status_level_)));
}

std::string StatusTreeItem::name_str()
{
    return name_;
}

std::string StatusTreeItem::value_str()
{
    return value_;
}

std::string StatusTreeItem::description_str()
{
    return description_;
}

int StatusTreeItem::recalculate_entity_counter()
{
    int count = 0;
    // check if top level item / entity item
    if (id_ != backend::ID_ALL && kind_ == backend::StatusKind::INVALID)
    {
        for (int i = 0; i < child_items_.count(); i++)
        {
            try
            {
                if (child_items_.value(i)->childCount() > 0)
                {
                    for (int j = 0; j < child_items_.value(i)->childCount(); j++)
                    {
                        count += child_items_.value(i)->child(j)->value().toInt();
                    }
                }
                count += child_items_.value(i)->value().toInt();
            }
            catch (...)
            {
            }
        }
        value_ = std::to_string(count);
        value_variant_ = QVariant(QString::fromStdString(value_));
    }
    return count;
}

} // namespace models
