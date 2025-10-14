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

#include <QDebug>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/backend/SyncBackendConnection.h>
#include <fastdds_monitor/model/alerts/AlertListItem.h>
#include <fastdds_monitor/model/SubListedListModel.h>
#include <fastdds_monitor/utils.h>

namespace models {

AlertListItem::AlertListItem(
        QObject* parent)
    : QObject(parent)
    , id_(0)
{
}

AlertListItem::AlertListItem(
        backend::AlertId id,
        QObject* parent)
    : QObject(parent)
    , id_(id)
{
}

AlertListItem::AlertListItem(
        backend::AlertId id,
        backend::AlertSummary info,
        QObject* parent)
    : QObject(parent)
    , id_(id)
    , info_(info)
    , clicked_(false)
{
}

AlertListItem::~AlertListItem()
{
}

QString AlertListItem::alert_id() const
{
    return backend::backend_id_to_models_id(id_); //backend::backend_id_to_models_id(id_);
}

QString AlertListItem::name() const
{
    return utils::to_QString(backend::get_alias(info_));
}

QString AlertListItem::kind() const
{
    return backend::alert_kind_to_QString(backend_kind());
}

bool AlertListItem::alive() const
{
    return backend::get_info_alive(info_);
}

bool AlertListItem::clicked() const
{
    return clicked_;
}

backend::AlertSummary AlertListItem::info() const
{
    return info_;
}

backend::AlertId AlertListItem::get_alert_id() const
{
    return id_;
}

QVariant AlertListItem::data(
        int role) const
{
    switch (role)
    {
        case idRole:
            return this->alert_id();
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

QHash<int, QByteArray> AlertListItem::roleNames() const
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
