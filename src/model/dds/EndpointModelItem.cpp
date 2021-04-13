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
           return this->entity_id();
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
    return backend::get_info_value(info_, "guid");
}

QString EndpointModelItem::topic() const
{
    return backend::get_info_value(info_, "topic");
}

QHash<int, QByteArray> EndpointModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles = ListItem::roleNames();

    roles[guidRole] = "guid";
    roles[topicRole] = "topic";

    return roles;
}

}
