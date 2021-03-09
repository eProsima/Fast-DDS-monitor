#ifndef HOSTMODELITEM_H
#define HOSTMODELITEM_H

#include <include/model/ListModel.h>
#include <include/model/SubListedListItem.h>

class HostModelItem : public models::SubListedListItem
{
    Q_OBJECT

public:

    enum HostModelItemRoles
    {
       hostIdRole = Qt::UserRole + 1,
    };

    HostModelItem(
            QString id,
            QObject* parent = 0);

    HostModelItem(
            QObject* parent = 0);

    ~HostModelItem();

    QString entityId() const;

    QVariant data(
            int role) const;

    QHash<int, QByteArray> roleNames() const;

    models::ListModel* submodel()  const;

protected:

    QString id_;
    models::ListModel* userListModel_;
};

#endif // HOSTMODELITEM_H
