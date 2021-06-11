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

#include <QStringList>

#include <fastdds_monitor/model/tree/TreeItem.h>

namespace models {

TreeItem::TreeItem(
        const QList<QString>& data,
        TreeItem* parent)
{
    parent_item_ = parent;
    item_data_ = data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(child_items_);
}

void TreeItem::append_child(
        TreeItem* item)
{
    child_items_.append(item);
}

TreeItem* TreeItem::child_item(
        int row)
{
    return child_items_.value(row);
}

int TreeItem::child_count() const
{
    return child_items_.count();
}

int TreeItem::column_count() const
{
    return item_data_.count();
}

QVariant TreeItem::data(
        int column) const
{
    return item_data_.value(column);
}

QVariant TreeItem::get_item_name() const
{
    return item_data_.value(TreeItemData::NAME);
}

QVariant TreeItem::get_item_value() const
{
    return item_data_.value(TreeItemData::VALUE);
}

QString TreeItem::name() const
{
    return get_item_name().toString();
}

TreeItem* TreeItem::parent_item()
{
    return parent_item_;
}

void TreeItem::clear()
{
    qDeleteAll(child_items_);
    child_items_.clear();
}

int TreeItem::row() const
{
    if (parent_item_)
    {
        return parent_item_->child_items_.indexOf(const_cast<TreeItem*>(this));
    }

    return 0;
}

} // namespace models

