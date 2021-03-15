#include <iostream>

#include <include/model/dds/EndpointModelItem.h>

#include <include/backend/backend_utils.h>

namespace models {

QVariant EndpointModelItem::data(
        int role) const
{
   switch (role)
   {
       case idRole:
           return this->entityId();
       case nameRole:
           return this->name();
       case guidRole:
           return this->guid();
       case topicRole:
           return this->topic();
       default:
           return QVariant();
   }
}

QString EndpointModelItem::guid() const
{
    return QString::fromUtf8("guid");
}

QString EndpointModelItem::topic() const
{
    return QString::fromUtf8("topic");
}

QHash<int, QByteArray> EndpointModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles = ListItem::roleNames();

    roles[guidRole] = "guid";
    roles[topicRole] = "topic";

    return roles;
}

}
