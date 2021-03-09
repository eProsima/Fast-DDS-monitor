#include <iostream>

#include <include/model/physical/ProcessModelItem.h>

ProcessModelItem::ProcessModelItem(
        QObject *parent)
    : ListItem(parent)
{
}

ProcessModelItem::ProcessModelItem(
        QString id,
        QString executable,
        QString pid,
        QObject *parent)
    : ListItem(parent)
    , id_(id)
    , executable_(executable)
    , pid_(pid)
{
}

QString ProcessModelItem::entityId() const
{
    return id_;
}

QVariant ProcessModelItem::data(
        int role) const
{
   switch (role)
   {
        case processIdRole:
           return this->entityId();
        case processExecRole:
            return this->executable_;
        case processPIDRole:
           return this->pid_;
        default:
           return QVariant();
   }
}

QHash<int, QByteArray> ProcessModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles;

    roles[processIdRole] = "processId";
    roles[processExecRole] = "processExec";
    roles[processPIDRole] = "processPID";

    return roles;
}
