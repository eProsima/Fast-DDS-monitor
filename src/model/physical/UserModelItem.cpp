#include <iostream>

#include <include/model/physical/UserModelItem.h>
#include <include/model/physical/ProcessModelItem.h>

UserModelItem::UserModelItem(
        QObject *parent)
    : SubListedListItem(parent)
{
    processListModel_ = new models::ListModel(new ProcessModelItem());
}

UserModelItem::UserModelItem(
        QString id,
        QString username,
        QObject *parent)
    : SubListedListItem(parent)
    , id_(id)
    , username_(username)
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
           return this->username_;
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

