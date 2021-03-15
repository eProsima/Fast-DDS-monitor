#ifndef PROCESSMODELITEM_H
#define PROCESSMODELITEM_H

#include <include/model/ListItem.h>

namespace models {

class ProcessModelItem : public ListItem
{
    Q_OBJECT

public:

    enum ProcessModelItemRoles
    {
        pidRole = ModelItemRoles::nameRole + 1,
    };

    ProcessModelItem(
            QObject *parent = 0)
        : ListItem(parent)
    {
    }

    ProcessModelItem(
            backend::EntityId id,
            QObject* parent = 0)
        : ListItem(id, parent)
    {
    }

    QVariant data(
            int role) const override;

    QString pid() const;

    QHash<int, QByteArray> roleNames() const override;
};

} //namespace models

#endif // PROCESSMODELITEM_H
