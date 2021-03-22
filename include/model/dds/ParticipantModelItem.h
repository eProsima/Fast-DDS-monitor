#ifndef PARTICIPANTMODELITEM_H
#define PARTICIPANTMODELITEM_H

#include <include/model/EntityContainerModelItem.h>
#include <include/model/SubListedListItem.h>
#include <include/model/dds/EndpointModelItem.h>

namespace models {

class ParticipantModelItem : public EntityContainerModelItem<EndpointModelItem, SubListedListModel>
{
    Q_OBJECT

public:

    enum ParticipantModelItemRoles
    {
        guidRole = ModelItemRoles::nameRole + 1,
        domainRole
    };

    ParticipantModelItem(
            QObject *parent = 0)
        : EntityContainerModelItem(parent)
    {
    }

    ParticipantModelItem(
            backend::EntityId id,
            QObject* parent = 0)
        : EntityContainerModelItem(id, parent)
    {
    }

    QVariant data(
            int role) const override;

    QString guid() const;
    QString domain() const;

    QHash<int, QByteArray> roleNames() const override;
};

}

#endif
