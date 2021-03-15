
#include <include/model/dds/ParticipantModelItem.h>

#include <include/backend/backend_utils.h>

namespace models {

QVariant ParticipantModelItem::data(
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
        case domainRole:
            return this->domain();
        default:
            return QVariant();
   }
}

QString ParticipantModelItem::guid() const
{
    return QString::fromUtf8("guid");
}

QString ParticipantModelItem::domain() const
{
    return QString::fromUtf8("domain");
}

QHash<int, QByteArray> ParticipantModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles = ListItem::roleNames();

    roles[guidRole] = "guid";
    roles[domainRole] = "domain";

    return roles;
}

}

