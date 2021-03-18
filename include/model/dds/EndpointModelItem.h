#ifndef ENDPOINTMODELITEM_H
#define ENDPOINTMODELITEM_H

#include <include/model/ListItem.h>
#include <include/model/dds/LocatorModelItem.h>
#include <include/model/EntityContainerModelItem.h>

namespace models {

class EndpointModelItem : public EntityContainerModelItem<LocatorModelItem, ListModel>
{
    Q_OBJECT

public:

    enum EndpointModelItemRoles
    {
        guidRole = ModelItemRoles::nameRole + 1,
        topicRole
    };

    EndpointModelItem(
            QObject *parent = 0)
        : EntityContainerModelItem(parent)
    {
    }

    EndpointModelItem(
            backend::EntityId id,
            QObject* parent = 0)
        : EntityContainerModelItem(id, parent)
    {
    }

    QVariant data(
            int role) const override;

    QString guid() const;
    QString topic() const;

    QHash<int, QByteArray> roleNames() const override;
};

}

#endif
