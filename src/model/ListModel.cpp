/****************************************************************************
**
** Copyright (C) Paul Lemire, Tepee3DTeam and/or its subsidiary(-ies).
** Contact: paul.lemire@epitech.eu
** Contact: tepee3d_2014@labeip.epitech.eu
**
** This file is part of the Tepee3D project
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
****************************************************************************/

#include <include/model/ListModel.h>
#include <include/backend/backend_types.h>
#include <include/utils.h>
// DEBUG
#include <iostream>
#include <QDebug>

namespace models {

ListModel::ListModel(
        ListItem *prototype,
        QObject *parent)
    : QAbstractListModel(parent)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    prototype_ = prototype;
    items_ = QList<ListItem*>();
}

ListModel::~ListModel()
{
    delete prototype_;
}

int ListModel::rowCount(
        const QModelIndex &) const
{
    return items_.size();
}

QVariant ListModel::data(
        const QModelIndex &index,
        int role) const
{
    if (index.row() >= 0 && index.row() < items_.size())
        return items_.at(index.row())->data(role);
    return QVariant();
}

QHash<int, QByteArray> ListModel::roleNames() const
{
        return prototype_->roleNames();
}

void ListModel::appendRow(
        ListItem* item)
{
    if (item != nullptr)
    {
        appendRows(QList<ListItem*>() << item);
        emit countChanged(rowCount());
    }
}

void ListModel::appendRows(QList<ListItem*> &items)
{
    if (items.size() == 0)
        return ;

    beginInsertRows(QModelIndex(), rowCount(), rowCount() + items.size() - 1);
    foreach(ListItem* item, items)
    {
        QObject::connect(item, SIGNAL(dataChanged()), this, SLOT(updateItem()));
        items_.append(item);
    }
    endInsertRows();

    emit countChanged(rowCount());
}

void ListModel::insertRow(
        int row,
        ListItem* item)
{
    if (item == nullptr)
        return;

    beginInsertRows(QModelIndex(), row, row);
    QObject::connect(item, SIGNAL(dataChanged()), this, SLOT(updateItem()));
    items_.insert(row, item);
    endInsertRows();
    emit countChanged(rowCount());
}

bool ListModel::removeRow(
        int row,
        const QModelIndex &index)
{
    if (row >= 0 && row < items_.size())
    {
        beginRemoveRows(index, row, row);
        ListItem* item = items_.takeAt(row);
        delete item;
        endRemoveRows();
        emit countChanged(rowCount());
        return true;
    }
    return false;
}

bool ListModel::removeRows(
        int row,
        int count,
        const QModelIndex &index)
{
    if (row >= 0 && count > 0 && (row + count) <= items_.size())
    {
        beginRemoveRows(index, row, row + count - 1);
        for (int i = 0; i < count; i++)
        {
            ListItem* item = items_.takeAt(row);
            delete item;
            item = nullptr;
        }
        endRemoveRows();
        emit countChanged(rowCount());
        return true;
    }
    return false;
}

void ListModel::clear()
{
    if (items_.size() == 0)
        return;
    removeRows(0, items_.size());
    emit countChanged(rowCount());
}

QModelIndex ListModel::indexFromItem(
        ListItem *item) const
{
    if (item != nullptr)
    {
        for (int i = 0; i < items_.size(); i++)
            if (items_.at(i) == item)
                return index(i);
    }
    return QModelIndex();
}

ListItem* ListModel::find(
        EntityId itemId) const
{
    foreach(ListItem *item, items_)
        if (item->entity_id() == itemId)
        {
            std::cout << "Found item with id: " << utils::to_string(itemId) << std::endl;
            return item;
        }
    std::cout << "Not found item with id: " << utils::to_string(itemId) << std::endl;
    return nullptr;
}

int ListModel::getRowFromItem(
        ListItem *item) const
{
    if (item != nullptr)
        for (int i = 0; i < items_.size(); i++)
            if (items_.at(i) == item)
                return i;
    return -1;
}

QList<ListItem*> ListModel::to_QList() const
{
    return items_;
}

void ListModel::updateItem()
{
    ListItem* item = static_cast<ListItem*>(sender());
    QModelIndex index = indexFromItem(item);
    if (index.isValid())
        emit dataChanged(index, index);
}

QVariant ListModel::get(
        int index)
{
    if (index >= items_.size() || index < 0)
        return QVariant();
    ListItem* item = items_.at(index);
    QMap<QString, QVariant> itemData;
    QHashIterator<int, QByteArray> hashItr(item->roleNames());

    while(hashItr.hasNext())
    {
        hashItr.next();
        itemData.insert(hashItr.value(),QVariant(item->data(hashItr.key())));
    }
    return QVariant(itemData);
}

int ListModel::rowIndexFromId(
        EntityId id)
{
    ListItem* item = find(id);

    if (item)
        return indexFromItem(item).row();
    return -1;
}

} // namespace models
