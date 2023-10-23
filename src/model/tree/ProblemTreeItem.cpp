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
#include <fastdds_monitor/model/tree/ProblemTreeModel.h>

namespace models {

ProblemTreeItem::ProblemTreeItem()
    : parent_item_(nullptr)
    , id_(backend::ID_ALL)
    , kind_(backend::StatusKind::INVALID)
    , name_()
    , is_status_error_(false)
    , value_()
    , description_()
    , is_active_(true)
    , id_variant_(QVariant(backend::backend_id_to_models_id(id_)))
    , kind_variant_(QVariant(QString::fromStdString(backend::status_kind_to_string(kind_))))
    , name_variant_(QVariant())
    , is_status_error_variant_(QVariant(false))
    , value_variant_(QVariant())
    , description_variant_(QVariant())
    , is_active_variant_(QVariant(true))
{
}

ProblemTreeItem::ProblemTreeItem(
        const QVariant& data)
    : parent_item_(nullptr)
    , id_(backend::ID_ALL)
    , kind_(backend::StatusKind::INVALID)
    , name_(data.toString().toStdString())
    , is_status_error_(false)
    , value_()
    , description_()
    , is_active_(true)
    , id_variant_(QVariant(backend::backend_id_to_models_id(id_)))
    , kind_variant_(QVariant(QString::fromStdString(backend::status_kind_to_string(kind_))))
    , name_variant_(QVariant(QString::fromStdString(name_)))
    , is_status_error_variant_(QVariant(false))
    , value_variant_(QVariant())
    , description_variant_(QVariant())
    , is_active_variant_(QVariant(true))
{
}

ProblemTreeItem::ProblemTreeItem(
        const backend::EntityId& id,
        const std::string& name,
        const bool& is_error,
        const std::string& description)
    : parent_item_(nullptr)
    , id_(id)
    , kind_(backend::StatusKind::INVALID)
    , name_(name)
    , is_status_error_(is_error)
    , value_()
    , description_(description)
    , is_active_(true)
    , id_variant_(QVariant(backend::backend_id_to_models_id(id_)))
    , kind_variant_(QVariant(QString::fromStdString(backend::status_kind_to_string(kind_))))
    , name_variant_(QVariant(QString::fromStdString(name)))
    , is_status_error_variant_(QVariant(is_error))
    , value_variant_(QVariant())
    , description_variant_(QVariant(QString::fromStdString(description)))
    , is_active_variant_(QVariant(true))
{
}

ProblemTreeItem::ProblemTreeItem(
        const backend::EntityId& id,
        const backend::StatusKind& kind,
        const std::string& name,
        const bool& is_error,
        const std::string& value,
        const std::string& description)
    : parent_item_(nullptr)
    , id_(id)
    , kind_(kind)
    , name_(name)
    , is_status_error_(is_error)
    , value_(value)
    , description_(description)
    , is_active_(true)
    , id_variant_(QVariant(backend::backend_id_to_models_id(id_)))
    , kind_variant_(QVariant(QString::fromStdString(backend::status_kind_to_string(kind_))))
    , name_variant_(QVariant(QString::fromStdString(name_)))
    , is_status_error_variant_(QVariant(is_error))
    , value_variant_(QVariant(QString::fromStdString(value)))
    , description_variant_(QVariant(QString::fromStdString(description)))
    , is_active_variant_(QVariant(true))
{
}

ProblemTreeItem::~ProblemTreeItem()
{
    qDeleteAll(child_items_);
}

ProblemTreeItem* ProblemTreeItem::parentItem()
{
    return parent_item_;
}

void ProblemTreeItem::setParentItem(
        ProblemTreeItem* parentItem)
{
    parent_item_ = parentItem;
}

void ProblemTreeItem::appendChild(
        ProblemTreeItem* item)
{
    if (item && !child_items_.contains(item))
    {
        child_items_.append(item);
    }
}

void ProblemTreeItem::removeChild(
        ProblemTreeItem* item)
{
    if (item)
    {
        child_items_.removeAll(item);
    }
}

ProblemTreeItem* ProblemTreeItem::child(
        int row)
{
    return child_items_.value(row);
}

int ProblemTreeItem::childCount() const
{
    return child_items_.count();
}

const QVariant& ProblemTreeItem::data() const
{
    return this->data(models::ProblemTreeModel::ModelItemRoles::nameRole);
}

const QVariant& ProblemTreeItem::data(
        int role) const
{
    switch (role)
    {
        case models::ProblemTreeModel::ModelItemRoles::idRole:
            return this->entity_id();
        case models::ProblemTreeModel::ModelItemRoles::statusRole:
            return this->status();
        case models::ProblemTreeModel::ModelItemRoles::kindRole:
            return this->status_kind();
        case models::ProblemTreeModel::ModelItemRoles::valueRole:
            return this->value();
        case models::ProblemTreeModel::ModelItemRoles::descriptionRole:
            return this->description();
        case models::ProblemTreeModel::ModelItemRoles::aliveRole:
            return this->alive();
        case models::ProblemTreeModel::ModelItemRoles::nameRole:
        default:
            return this->name();
    }
}

const QVariant& ProblemTreeItem::entity_id() const
{
    return  id_variant_;
}

const QVariant& ProblemTreeItem::status_kind() const
{
    return  kind_variant_;
}

const QVariant& ProblemTreeItem::name() const
{
    return name_variant_;
}

const QVariant& ProblemTreeItem::status() const
{
    return is_status_error_variant_;
}

const QVariant& ProblemTreeItem::value() const
{
    return value_variant_;
}

const QVariant& ProblemTreeItem::description() const
{
    return description_variant_;
}

const QVariant& ProblemTreeItem::alive() const
{
    return is_active_variant_;
}

void ProblemTreeItem::setData(
        const QVariant& data)
{
    name_variant_ = data;
}

bool ProblemTreeItem::isLeaf() const
{
    return child_items_.isEmpty();
}

int ProblemTreeItem::depth() const
{
    int depth = 0;
    ProblemTreeItem* anchestor = parent_item_;
    while (anchestor)
    {
        ++depth;
        anchestor = anchestor->parentItem();
    }

    return depth;
}

int ProblemTreeItem::row() const
{
    if (parent_item_)
    {
        return parent_item_->child_items_.indexOf(const_cast<ProblemTreeItem*>(this));
    }

    return 0;
}

backend::EntityId ProblemTreeItem::id()
{
    return id_;
}

backend::StatusKind ProblemTreeItem::kind()
{
    return kind_;
}


int ProblemTreeItem::recalculate_entity_counter()
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
            catch (...) {}
        }
        value_ = std::to_string(count);
        value_variant_ = QVariant(QString::fromStdString(value_));
    }
    return count;
}

} // namespace models
