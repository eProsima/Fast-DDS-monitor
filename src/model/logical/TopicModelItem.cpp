
#include <include/model/logical/TopicModelItem.h>

#include <include/backend/backend_utils.h>

namespace models {

QVariant TopicModelItem::data(
        int role) const
{
   switch (role)
   {
        case idRole:
           return this->entityId();
        case nameRole:
            return this->name();
        case typeRole:
           return this->type();
        default:
           return QVariant();
   }
}

QString TopicModelItem::type() const
{
    return QString::fromUtf8("topic type name");
}


QHash<int, QByteArray> TopicModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles = ListItem::roleNames();

    roles[typeRole] = "type";

    return roles;
}

} // namespace models
