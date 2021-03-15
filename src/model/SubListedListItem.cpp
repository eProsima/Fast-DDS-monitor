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

#include <include/model/SubListedListItem.h>
#include <include/backend/backend_types.h>
#include <include/model/SubListedListModel.h>
#include <include/utils.h>
// DEBUG
#include <iostream>
#include <QDebug>

namespace models {

SubListedListItem::SubListedListItem(
        QObject *parent)
    : QObject(parent)
{
    subEntitiesListModel_ = new models::SubListedListModel(new SubEntityClass());
}

SubListedListItem::SubListedListItem(
        backend::EntityId id,
        QObject* parent)
    : QObject(parent)
    , id_(id)
{
    subEntitiesListModel_ = new models::SubListedListModel(new SubEntityClass());
}

SubListedListItem::~SubListedListItem()
{
    subEntitiesListModel_->clear();
    delete subEntitiesListModel_;
}

ListModel* SubListedListItem::submodel() const
{
    std::cout << "Getting submodule from : " << utils::to_string(name()) << std::endl;
    return subEntitiesListModel_;
}

} //namespace models
