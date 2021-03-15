#include <iostream>

#include <include/model/logical/DomainModelItem.h>
//#include <include/backend/backend_utils.h>

DomainModelItem::DomainModelItem(
        QObject *parent)
    : ListItem(parent)
{
}

DomainModelItem::DomainModelItem(
        backend::EntityId id,
        QObject *parent)
    : ListItem(parent)
    , id_(id)
{
}

QString DomainModelItem::entityId() const
{
    return QString();
//    return backend::id_to_QString(id_);
}

QString DomainModelItem::name() const
{
    return QString();
//    return backend::id_to_QString(id_);
}

backend::EntityId DomainModelItem::get_entityId() const
{
    return id_;
}

QVariant DomainModelItem::data(
        int role) const
{
   switch (role)
   {
        case domainIdRole:
           return this->entityId();
        case domainNameRole:
            return this->name();
        default:
           return QVariant();
   }
}

QHash<int, QByteArray> DomainModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles;

    roles[domainIdRole] = "domainId";
    roles[domainNameRole] = "domainName";

    return roles;
}
