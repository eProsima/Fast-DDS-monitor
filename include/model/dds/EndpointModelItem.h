#ifndef ENDPOINTMODELITEM_H
#define ENDPOINTMODELITEM_H

#include <include/model/ListItem.h>

namespace models {

class EndpointModelItem : public ListItem
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
        : ListItem(parent)
    {
    }

    EndpointModelItem(
            backend::EntityId id,
            QObject* parent = 0)
        : ListItem(id, parent)
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
