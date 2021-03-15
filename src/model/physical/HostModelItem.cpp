#include <iostream>

#include <include/model/physical/HostModelItem.h>
#include <include/model/SubListedListModel.h>
#include <include/model/physical/UserModelItem.h>

#include <include/backend/backend_types.h>
#include <include/backend/backend_utils.h>

HostModelItem::HostModelItem(QObject *parent)
    : SubListedListItem(parent)
{
    userListModel_ = new models::SubListedListModel(new UserModelItem());
}

HostModelItem::HostModelItem(
        backend::EntityId id,
        QObject *parent)
    : SubListedListItem(parent)
    , id_(id)
{
    userListModel_ = new models::SubListedListModel(new UserModelItem());
}

HostModelItem::~HostModelItem()
{
    userListModel_->clear();
    delete userListModel_;
}

QString HostModelItem::entityId() const
{
    return backend::backend_id_to_model_id(id_);
}

backend::EntityId HostModelItem::get_entityId() const
{
    return id_;
}

QVariant HostModelItem::data(int role) const
{
    switch (role)
    {
        case hostIdRole:
            return this->entityId();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> HostModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles;

    roles[hostIdRole] = "hostId";

    return roles;
}

models::ListModel* HostModelItem::submodel() const
{
    return userListModel_;
}

