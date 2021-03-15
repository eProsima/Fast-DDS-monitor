#include <iostream>

#include <include/model/physical/UserModelItem.h>
#include <include/model/physical/ProcessModelItem.h>

#include <include/backend/backend_types.h>
#include <include/backend/backend_utils.h>

UserModelItem::UserModelItem(
        QObject *parent)
    : SubListedListItem(parent)
{
    processListModel_ = new models::ListModel(new ProcessModelItem());
}

UserModelItem::UserModelItem(
        backend::EntityId id,
        QObject *parent)
    : SubListedListItem(parent)
    , id_(id)
{
    processListModel_ = new models::ListModel(new ProcessModelItem());
}

UserModelItem::~UserModelItem()
{
    processListModel_->clear();
    delete processListModel_;
}

QString UserModelItem::entityId() const
{
    return backend::backend_id_to_model_id(id_);
}

QString UserModelItem::username() const
{
    return backend::id_to_QString(id_);
}

backend::EntityId UserModelItem::get_entityId() const
{
    return id_;
}

QVariant UserModelItem::data(
        int role) const
{
   switch (role)
   {
       case userIdRole:
           return this->entityId();
       case usernameRole:
           return this->username();
       default:
           return QVariant();
   }
}

QHash<int, QByteArray> UserModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles;

    roles[userIdRole] = "userId";
    roles[usernameRole] = "username";

    return roles;
}

models::ListModel* UserModelItem::submodel() const
{
    return processListModel_;
}

