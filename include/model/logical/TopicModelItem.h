#ifndef TOPCIMODELITEM_H
#define TOPICMODELITEM_H

#include <include/model/ListItem.h>
#include <include/model/SubListedListItem.h>

class TopicModelItem : public models::ListItem
{
    Q_OBJECT

public:

    enum TopicModelItemRoles
    {
       topicIdRole = Qt::UserRole + 1,
       topicNameRole,
       topicDataTypeRole
    };

    TopicModelItem(
            QObject *parent = 0);

    TopicModelItem(
            QString id,
            QString name,
            QString type,
            QObject *parent = 0);

    QString entityId() const;

    QVariant data(
            int role) const;

    QHash<int, QByteArray> roleNames() const;

protected:

    QString id_;
    QString name_;
    QString type_;
};

#endif // TOPICMODELITEM_H
