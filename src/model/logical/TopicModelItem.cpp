#include <iostream>

#include <include/model/logical/TopicModelItem.h>

TopicModelItem::TopicModelItem(
        QObject *parent)
    : ListItem(parent)
{
}

TopicModelItem::TopicModelItem(
        QString id,
        QString name,
        QString type,
        QObject *parent)
    : ListItem(parent)
    , id_(id)
    , name_(name)
    , type_(type)
{
}

QString TopicModelItem::entityId() const
{
    return id_;
}

QVariant TopicModelItem::data(
        int role) const
{
   switch (role)
   {
        case topicIdRole:
           return this->entityId();
        case topicNameRole:
            return this->name_;
        case topicDataTypeRole:
           return this->type_;
        default:
           return QVariant();
   }
}

QHash<int, QByteArray> TopicModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles;

    roles[topicIdRole] = "topicId";
    roles[topicNameRole] = "topicName";
    roles[topicDataTypeRole] = "topicDataType";

    return roles;
}
