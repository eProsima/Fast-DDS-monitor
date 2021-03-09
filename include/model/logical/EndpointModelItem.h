#ifndef ENDPOINTMODELITEM_H
#define ENDPOINTMODELITEM_H

#include <include/model/ListModel.h>
#include <include/model/SubListedListItem.h>

class EndpointModelItem : public models::SubListedListItem
{
    Q_OBJECT

public:
    enum EndpointModelItemRoles
    {
       endpointGuidRole = Qt::UserRole + 1,
       endpointTypeRole
    };

    EndpointModelItem(
            QObject *parent = 0);

    EndpointModelItem(
            QString guid,
            QString type,
            QObject* parent = 0);

    ~EndpointModelItem();

    QString entityId() const;

    QVariant data(
            int role) const;

    QHash<int, QByteArray> roleNames() const;

    models::ListModel* submodel() const;

protected:
    QString guid_;
    QString type_;
    models::ListModel* topicListModel_;
};

#endif
