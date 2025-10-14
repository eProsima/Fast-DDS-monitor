// Copyright 2025 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include <QQmlEngine>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/model/alerts/AlertListModel.h>
#include <fastdds_monitor/utils.h>

namespace models {

AlertListModel::AlertListModel(
        AlertListItem* prototype,
        QObject* parent)
    : QAbstractListModel(parent)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    prototype_ = prototype;
    items_ = QList<AlertListItem*>();
}

AlertListModel::~AlertListModel()
{
    delete prototype_;
}

int AlertListModel::rowCount(
        const QModelIndex&) const
{
    return items_.size();
}

QVariant AlertListModel::data(
        const QModelIndex& index,
        int role) const
{
    if (index.row() >= 0 && index.row() < items_.size())
    {
        return items_.at(index.row())->data(role);
    }
    return QVariant();
}

QHash<int, QByteArray> AlertListModel::roleNames() const
{
    return prototype_->roleNames();
}

void AlertListModel::appendRow(
        AlertListItem* item)
{
    if (item != nullptr)
    {
        appendRows(QList<AlertListItem*>() << item);
        emit countChanged(rowCount());
    }
}

void AlertListModel::appendRows(
        QList<AlertListItem*>& items)
{
    if (items.size() == 0)
    {
        return;
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount() + items.size() - 1);
    foreach(AlertListItem * item, items)
    {
        QObject::connect(item, SIGNAL(dataChanged()), this, SLOT(updateItem()));
        items_.append(item);
    }
    endInsertRows();

    emit countChanged(rowCount());
}

void AlertListModel::insertRow(
        int row,
        AlertListItem* item)
{
    if (item == nullptr)
    {
        return;
    }

    beginInsertRows(QModelIndex(), row, row);
    QObject::connect(item, SIGNAL(dataChanged()), this, SLOT(updateItem()));
    items_.insert(row, item);
    endInsertRows();
    emit countChanged(rowCount());
}

bool AlertListModel::removeRow(
        int row,
        const QModelIndex& index)
{
    if (row >= 0 && row < items_.size())
    {
        beginRemoveRows(index, row, row);
        AlertListItem* item = items_.takeAt(row);
        delete item;
        endRemoveRows();
        emit countChanged(rowCount());
        return true;
    }
    return false;
}

bool AlertListModel::removeRows(
        int row,
        int count,
        const QModelIndex& index)
{
    if (row >= 0 && count > 0 && (row + count) <= items_.size())
    {
        beginRemoveRows(index, row, row + count - 1);
        for (int i = 0; i < count; i++)
        {
            AlertListItem* item = items_.takeAt(row);
            delete item;
            item = nullptr;
        }
        endRemoveRows();
        emit countChanged(rowCount());
        return true;
    }
    return false;
}

void AlertListModel::clear()
{
    if (items_.size() == 0)
    {
        return;
    }
    removeRows(0, items_.size());
    emit countChanged(rowCount());
}

QModelIndex AlertListModel::indexFromItem(
        AlertListItem* item) const
{
    if (item != nullptr)
    {
        for (int i = 0; i < items_.size(); i++)
        {
            if (items_.at(i) == item)
            {
                return index(i);
            }
        }
    }
    return QModelIndex();
}

AlertListItem* AlertListModel::find(
        AlertId itemId) const
{
    foreach(AlertListItem * item, items_)
    {
        if (item->alert_id() == itemId)
        {
            return item;
        }
    }
    return nullptr;
}

AlertListItem* AlertListModel::find(
        backend::AlertId itemId) const
{
    foreach(AlertListItem * item, items_)
    {
        if (item->get_alert_id() == itemId)
        {
            return item;
        }
    }
    return nullptr;
}

AlertListItem* AlertListModel::at(
        int index) const
{
    return items_.at(index);
}

int AlertListModel::getRowFromItem(
        AlertListItem* item) const
{
    if (item != nullptr)
    {
        for (int i = 0; i < items_.size(); i++)
        {
            if (items_.at(i) == item)
            {
                return i;
            }
        }
    }
    return -1;
}

QList<AlertListItem*> AlertListModel::to_QList() const
{
    return items_;
}

void AlertListModel::updateItem()
{
    AlertListItem* item = static_cast<AlertListItem*>(sender());
    QModelIndex index = indexFromItem(item);
    if (index.isValid())
    {
        emit dataChanged(index, index);
    }
}

QVariant AlertListModel::get(
        int index)
{
    if (index >= items_.size() || index < 0)
    {
        return QVariant();
    }
    AlertListItem* item = items_.at(index);
    QMap<QString, QVariant> itemData;
    QHashIterator<int, QByteArray> hashItr(item->roleNames());

    while (hashItr.hasNext())
    {
        hashItr.next();
        itemData.insert(hashItr.value(), QVariant(item->data(hashItr.key())));
    }
    return QVariant(itemData);
}

int AlertListModel::rowIndexFromId(
        AlertId id)
{
    AlertListItem* item = find(id);

    if (item)
    {
        return indexFromItem(item).row();
    }
    return -1;
}

int AlertListModel::rowIndexFromId(
        backend::AlertId id)
{
    AlertListItem* item = find(id);

    if (item)
    {
        return indexFromItem(item).row();
    }
    return -1;
}

} // namespace models
