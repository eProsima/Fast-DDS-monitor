#ifndef PROCESSMODELITEM_H
#define PROCESSMODELITEM_H

#include <include/model/ListItem.h>
#include <include/model/SubListedListItem.h>

class ProcessModelItem : public models::ListItem
{
    Q_OBJECT

public:

    enum ProcessModelItemRoles
    {
       processIdRole = Qt::UserRole + 1,
       processExecRole,
       processPIDRole
    };

    ProcessModelItem(
            QObject *parent = 0);

    ProcessModelItem(
            QString id,
            QString executable,
            QString pid,
            QObject *parent = 0);

    QString entityId() const;

    QVariant data(
            int role) const;

    QHash<int, QByteArray> roleNames() const;

protected:

    QString id_;
    QString executable_;
    QString pid_;
};

#endif // PROCESSMODELITEM_H
