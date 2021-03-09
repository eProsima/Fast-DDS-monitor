#ifndef USERMODELITEM_H
#define USERMODELITEM_H

#include <include/model/ListModel.h>
#include <include/model/SubListedListItem.h>

class UserModelItem : public models::SubListedListItem
{
    Q_OBJECT

public:
    enum UserModelItemRoles
    {
       userIdRole = Qt::UserRole + 1,
       usernameRole
    };

    UserModelItem(
            QObject *parent = 0);

    UserModelItem(
            QString id,
            QString username,
            QObject* parent = 0);

    ~UserModelItem();

    QString entityId() const;

    QVariant data(
            int role) const;

    QHash<int, QByteArray> roleNames() const;

    models::ListModel* submodel() const;

protected:
    QString id_;
    QString username_;
    models::ListModel* processListModel_;
};

#endif
