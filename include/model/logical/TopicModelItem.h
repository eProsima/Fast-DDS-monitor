#ifndef TOPICMODELITEM_H
#define TOPICMODELITEM_H

#include <include/model/ListItem.h>

namespace models {

class TopicModelItem : public ListItem
{
    Q_OBJECT

public:

    enum TopicModelItemRoles
    {
        typeRole = ModelItemRoles::nameRole + 1,
    };

    TopicModelItem(
            QObject *parent = 0)
        : ListItem(parent)
    {
    }

    TopicModelItem(
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

#endif // TOPICMODELITEM_H
