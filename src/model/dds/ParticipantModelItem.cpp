
#include <include/model/dds/ParticipantModelItem.h>

#include <include/backend/backend_utils.h>

namespace models {

QVariant ParticipantModelItem::data(
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
        case domainRole:
            return this->domain();
        default:
            return QVariant();
   }
}

QString ParticipantModelItem::guid() const
{
    return backend::get_info_value(info_, "guid");
}

QString ParticipantModelItem::domain() const
{
    return backend::get_info_value(info_, "domain");
}

QHash<int, QByteArray> ParticipantModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles = ListItem::roleNames();

    roles[guidRole] = "guid";
    roles[domainRole] = "domain";

    return roles;
}

}

