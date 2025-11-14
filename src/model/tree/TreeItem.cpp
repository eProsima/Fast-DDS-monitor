// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

TreeItem* TreeItem::take_child_item(
        int row)
{
    return child_items_.takeAt(row);
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

void TreeItem::set_item_value(
        const QVariant& value)
{
    item_data_[TreeItemData::VALUE] = value.toString();
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

