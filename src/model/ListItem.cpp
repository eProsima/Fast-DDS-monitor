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

#include <QDebug>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/backend/SyncBackendConnection.h>
#include <fastdds_monitor/model/ListItem.h>
#include <fastdds_monitor/model/SubListedListModel.h>
#include <fastdds_monitor/utils.h>

namespace models {

ListItem::ListItem(
        QObject* parent)
    : QObject(parent)
    , id_(backend::EntityId::invalid())
{
}

ListItem::ListItem(
        backend::EntityId id,
        QObject* parent)
    : QObject(parent)
    , id_(id)
{
}

ListItem::ListItem(
        backend::EntityId id,
        backend::EntityInfo info,
        QObject* parent)
    : QObject(parent)
    , id_(id)
    , info_(info)
    , clicked_(false)
{
}

ListItem::~ListItem()
{
}

QString ListItem::entity_id() const
{
    return backend::backend_id_to_models_id(id_); //backend::backend_id_to_models_id(id_);
}

QString ListItem::name() const
{
    return utils::to_QString(backend::get_alias(info_));
}

QString ListItem::kind() const
{
    return backend::entity_kind_to_QString(backend_kind());
}

bool ListItem::alive() const
{
    return backend::get_info_alive(info_);
}

bool ListItem::clicked() const
{
    return clicked_;
}

backend::EntityInfo ListItem::info() const
{
    return info_;
}

backend::EntityId ListItem::get_entity_id() const
{
    return id_;
}

QVariant ListItem::data(
        int role) const
{
    switch (role)
    {
        case idRole:
            return this->entity_id();
        case nameRole:
            return this->name();
        case kindRole:
            return this->kind();
        case aliveRole:
            return this->alive();
        case clickedRole:
            return this->clicked();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ListItem::roleNames() const
{
    QHash<int, QByteArray>  roles;

    roles[idRole] = "id";
    roles[nameRole] = "name";
    roles[kindRole] = "kind";
    roles[aliveRole] = "alive";
    roles[clickedRole] = "clicked";

    return roles;
}

} //namespace models
