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

#include <fastdds-monitor/backend/backend_types.h>
#include <fastdds-monitor/model/ListItem.h>
#include <fastdds-monitor/model/SubListedListModel.h>
#include <fastdds-monitor/utils.h>

namespace models {

ListItem::ListItem(
        QObject* parent)
    : QObject(parent)
{
}

ListItem::ListItem(
        backend::EntityId id,
        QObject* parent)
    : QObject(parent)
    , id_(id)
{
    info_ = backend::get_info(id_);
}

ListItem::~ListItem()
{
}

QString ListItem::entity_id() const
{
    return backend::id_to_QString(id_); //backend::id_to_QString(id_);
}

QString ListItem::name() const
{
    return utils::to_QString(backend::get_info_value(info_, "name"));
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
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ListItem::roleNames() const
{
    QHash<int, QByteArray>  roles;

    roles[idRole] = "id";
    roles[nameRole] = "name";

    return roles;
}

} //namespace models
