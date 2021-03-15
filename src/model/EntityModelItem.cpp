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

#include <include/model/ListItem.h>
#include <include/backend/backend_types.h>
#include <include/model/SubListedListModel.h>
#include <include/utils.h>
// DEBUG
#include <iostream>
#include <QDebug>

using namespace models;

ListItem::~ListItem()
{
    subEntitiesListModel_->clear();
    delete subEntitiesListModel_;
}

models::EntityId ListItem::entityId() const
{
    return backend::backend_id_to_model_id(id_);
}

QString ListItem::name() const
{
    return backend::get_name(id_);
}

backend::EntityId ListItem::get_entityId() const
{
    return id_;
}

QVariant ListItem::data(
        int role) const
{
    switch (role)
    {
        case idRole:
            return this->entityId();
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


ListModel* ListItem::submodel() const
{
    return subEntitiesListModel_;
}
