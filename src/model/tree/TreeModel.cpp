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
#include <fastdds_monitor/model/tree/TreeModel.h>

namespace models {

TreeModel::TreeModel(
        const json& data,
        QObject* parent)
    : QAbstractItemModel(parent)
{
    root_item_ = new TreeItem(QList<QString>() << "Name" << "Value");
    setup_model_data(data, root_item_);
}

TreeModel::TreeModel(
        QObject* parent)
    : QAbstractItemModel(parent)
{
    root_item_ = new TreeItem(QList<QString>() << "Name" << "Value");
}

TreeModel::~TreeModel()
{
    beginResetModel();
    root_item_->clear();
    endResetModel();
    delete root_item_;
}

int TreeModel::columnCount(
        const QModelIndex& parent) const
{
    if (parent.isValid())
    {
        return get_item(parent)->column_count();
    }
    else
    {
        return root_item_->column_count();
    }
}

QVariant TreeModel::data(
        const QModelIndex& index,
        int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    TreeItem* child_item = get_item(index);

    if (child_item != nullptr)
    {
        switch (role)
        {
            case treeModelNameRole:
                return child_item->get_item_name();
            case treeModelValueRole:
                return child_item->get_item_value();
            default:
                return QVariant();
        }
    }

    return QVariant();
}

Qt::ItemFlags TreeModel::flags(
        const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return QAbstractItemModel::flags(index);
}

QModelIndex TreeModel::index(
        int row,
        int column,
        const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    TreeItem* parent_item;
    if (!parent.isValid())
    {
        parent_item = root_item_;
    }
    else
    {
        parent_item = static_cast<TreeItem*>(parent.internalPointer());
    }

    TreeItem* child_item = parent_item->child_item(row);
    if (child_item)
    {
        return createIndex(row, column, child_item);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex TreeModel::parent(
        const QModelIndex& index) const
{

    TreeItem* parent_item = nullptr;
    TreeItem* child_item = nullptr;

    if (!index.isValid())
    {
        return QModelIndex();
    }

    if (parent_item == root_item_)
    {
        return QModelIndex();
    }

    if ((child_item = get_item(index)) != nullptr)
    {
        if ((parent_item = child_item->parent_item()) != nullptr)
        {
            return createIndex(parent_item->row(), 0, parent_item);
        }
    }

    return QModelIndex();
}

int TreeModel::rowCount(
        const QModelIndex& parent) const
{
    TreeItem* parent_item;
    if (parent.column() > 0)
    {
        return 0;
    }

    if (!parent.isValid())
    {
        parent_item = root_item_;
    }
    else
    {
        parent_item = get_item(parent);
    }

    return parent_item->child_count();
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[treeModelNameRole] = "name";
    roles[treeModelValueRole] = "value";

    return roles;
}

TreeItem* TreeModel::get_item(
        const QModelIndex& index) const
{

    TreeItem* item = nullptr;

    if (index.isValid())
    {
        item = static_cast<TreeItem*>(index.internalPointer());
        if (item != nullptr)
        {
            return item;
        }
    }

    return root_item_;
}

void TreeModel::setup_model_data(
        const json& json_data,
        TreeItem* parent,
        bool _first /* = true */)
{
    QList<QString> data;

    bool last_child = false;

    json value;

    for (json::const_iterator it = json_data.begin(); it != json_data.end(); ++it)
    {
        data << QString::fromUtf8(it.key().c_str());

        if (it.value().is_primitive())
        {
            if (it.value().is_string())
            {
                data << QString::fromUtf8(static_cast<std::string>(it.value()).c_str());
                last_child = true;
            }
            else if (it.value().is_number())
            {
                data << QString::number(static_cast<int>(it.value()));
                last_child = true;
            }
            else if (it.value().is_boolean())
            {
                data << (it.value() ? QString("true") : QString("false"));
                last_child = true;
            }
            else
            {
                data << "-";
                last_child = true;
            }
        }

        TreeItem* current_child = new TreeItem(data, parent);
        if (!last_child)
        {
            setup_model_data(static_cast<json>(it.value()), current_child, false);
        }

        parent->append_child(current_child);
        data.clear();


        last_child = false;
    }

    // Add a final void element to avoid TreeView collapse fail
    if (_first)
    {
        TreeItem* empty_child = new TreeItem(data, parent);
        parent->append_child(empty_child);
    }
}

void TreeModel::clear()
{
    root_item_->clear();
}

void TreeModel::update(
        json data)
{
    std::unique_lock<std::mutex> lock(update_mutex_);

    beginResetModel();
    clear();
    setup_model_data(data, root_item_);
    endResetModel();
    emit updatedData();
}

} // namespace models
