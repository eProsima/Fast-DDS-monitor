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

#include <QDebug>

#include <fastdds_monitor/backend/backend_utils.h>
#include <fastdds_monitor/model/statistics/EntityItem.h>

namespace models {

QVariant EntityItem::data(
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
        case nameIdRole:
            return this->nameId();
        default:
            return QVariant();
    }
}

QString EntityItem::nameId() const
{
    QString nameId = name();
    nameId.append(":<");
    nameId.append(entity_id());
    nameId.append(">");
    return nameId;
}

QHash<int, QByteArray> EntityItem::roleNames() const
{
    QHash<int, QByteArray>  roles = ListItem::roleNames();

    roles[nameIdRole] = "nameId";

    return roles;
}

} // namespace models
