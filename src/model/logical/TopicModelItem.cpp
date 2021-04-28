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

#include <fastdds-monitor/backend/backend_utils.h>
#include <fastdds-monitor/model/logical/TopicModelItem.h>

namespace models {

QVariant TopicModelItem::data(
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
        case typeRole:
            return this->type();
        default:
            return QVariant();
    }
}

QString TopicModelItem::type() const
{
    return utils::to_QString(backend::get_info_value(info_, "topic"));
}

QHash<int, QByteArray> TopicModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles = ListItem::roleNames();

    roles[typeRole] = "type";

    return roles;
}

} // namespace models
