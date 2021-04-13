#ifndef ENTITYITEM_H
#define ENTITYITEM_H

#include <include/model/ListItem.h>

namespace models {

class EntityItem : public ListItem
{
    Q_OBJECT

public:

    EntityItem(
            QObject *parent = 0)
        : ListItem(parent)
    {
    }

    EntityItem(
            backend::EntityId id,
            QObject* parent = 0)
        : ListItem(id, parent)
    {
    }

    QVariant data(
            int role) const override;

    QString type() const;

    QHash<int, QByteArray> roleNames() const override;
};

} //namespace models

#endif // ENTITYITEM_H
