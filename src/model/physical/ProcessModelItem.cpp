
#include <include/model/physical/ProcessModelItem.h>

#include <include/backend/backend_utils.h>

namespace models {

QVariant ProcessModelItem::data(
        int role) const
{
   switch (role)
   {
        case idRole:
           return this->entity_id();
        case nameRole:
            return this->name();
        case pidRole:
           return this->pid();
        default:
           return QVariant();
   }
}

QString ProcessModelItem::pid() const
{
    return utils::to_QString(info_["pid"]);
}


QHash<int, QByteArray> ProcessModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles = ListItem::roleNames();

    roles[pidRole] = "processPID";

    return roles;
}

}
