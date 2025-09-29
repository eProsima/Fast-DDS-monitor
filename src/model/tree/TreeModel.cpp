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

#include <QHash>
#include <QSet>
#include <QString>
#include <QStringList>
#include <QHash>
#include <QSet>

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

TreeItem* TreeModel::find_child_by_name(TreeItem* parent, const QString& name) const
{
    for (int i = 0; i < parent->child_count(); ++i)
    {
        TreeItem* child = parent->child_item(i);
        if (child->get_item_name().toString() == name)
            return child;
    }
    return nullptr;
}

void TreeModel::setup_model_data_without_clean(TreeItem* parent, const QModelIndex& parent_index, const json& json_data)
{
    QHash<QString, int> currentIndexByName;
    for (int i = 0; i < parent->child_count(); ++i)
    {
        QString name = parent->child_item(i)->get_item_name().toString();
        currentIndexByName[name] = i;
    }

    QSet<QString> newKeys;
    int insertPos = parent->child_count();
    int jsonIndex = 0;
    for (auto it = json_data.begin(); it != json_data.end(); ++it, ++jsonIndex)
    {
        QString key = QString::fromUtf8(it.key().c_str());
        newKeys.insert(key);

        TreeItem* existingChild = find_child_by_name(parent, key);

        if (existingChild)
        {
            // If the node exists, its content might be updated
            if (it.value().is_primitive())
            {
                QString newValue;
                if (it.value().is_string())
                    newValue = QString::fromUtf8(it.value().get<std::string>().c_str());
                else if (it.value().is_number())
                    newValue = QString::number(it.value().get<int>());
                else if (it.value().is_boolean())
                    newValue = (it.value().get<bool>() ? "true" : "false");
                else
                    newValue = "-";

                // Update value if changed
                if (existingChild->get_item_value().toString() != newValue)
                {
                    // Replace the value directly in TreeItem
                    existingChild->data(TreeItem::VALUE); // ensure correct access
                    existingChild->clear(); // if needed to reset children
                    // Update internal value
                    QList<QString> updatedData;
                    updatedData << key << newValue;
                    *existingChild = TreeItem(updatedData, parent);
                    // Notify QML about the change
                    QModelIndex changedIndex = createIndex(existingChild->row(), 1, existingChild);
                    emit dataChanged(changedIndex, changedIndex);
                }
            }
            else
            {
                // Recurse deeper for nested structures
                QModelIndex childIndex = createIndex(existingChild->row(), 0, existingChild);
                setup_model_data_without_clean(existingChild, childIndex, it.value());
            }
        }
        else
        {
            // If it does not exist, it is inserted
            beginInsertRows(parent_index, insertPos, insertPos);

            QList<QString> rowData;
            rowData << key;

            if (it.value().is_primitive())
            {
                if (it.value().is_string())
                    rowData << QString::fromUtf8(it.value().get<std::string>().c_str());
                else if (it.value().is_number())
                    rowData << QString::number(it.value().get<int>());
                else if (it.value().is_boolean())
                    rowData << (it.value().get<bool>() ? "true" : "false");
                else
                    rowData << "-";
            }
            else
            {
                rowData << "";
            }

            TreeItem* newChild = new TreeItem(rowData, parent);
            parent->append_child(newChild);

            endInsertRows();

            if (!it.value().is_primitive())
            {
                QModelIndex newIndex = createIndex(insertPos, 0, newChild);
                setup_model_data_without_clean(newChild, newIndex, it.value());
            }

            insertPos++;
        }
    }

    // Remove nodes that are not present in the data
    for (int i = parent->child_count() - 1; i >= 0; --i)
    {
        TreeItem* child = parent->child_item(i);
        QString name = child->get_item_name().toString();

        if (!newKeys.contains(name))
        {
            beginRemoveRows(parent_index, i, i);
            delete child;
            parent->remove_child_item(i); // direct removal
            endRemoveRows();
        }
    }
}

void TreeModel::update_without_clean(json& data)
{
    std::unique_lock<std::mutex> lock(update_mutex_);
    // Recursive function to update without cleaning the entire model
    setup_model_data_without_clean(root_item_, QModelIndex(), data);
    emit updatedData();
}

} // namespace models
