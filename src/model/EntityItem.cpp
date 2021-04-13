#include <include/model/EntityItem.h>

#include <include/backend/backend_utils.h>

namespace models {

QVariant EntityItem::data(
        int role) const
{
   switch (role)
   {
        case idRole:
           return this->entity_id();
        case nameRole:
            return this->name();
        default:
           return QVariant();
   }
}

QHash<int, QByteArray> EntityItem::roleNames() const
{
    QHash<int, QByteArray> roles = ListItem::roleNames();

    return roles;
}

} // namespace models
