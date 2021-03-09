#ifndef LISTITEM_H
#define LISTITEM_H

#include <QObject>
#include <QVariant>
#include <QHash>

namespace models
{

class ListItem : public QObject
{
    Q_OBJECT

public :

    ListItem(
            QObject *parent = 0)
        : QObject(parent)
    {
    }

    virtual ~ListItem()
    {
    }

    virtual QString entityId() const = 0;

    virtual QVariant data(
            int role) const = 0;

    virtual QHash<int, QByteArray> roleNames() const = 0;

    virtual void triggerItemUpdate()
    {
        emit dataChanged();
    }

signals:

    void dataChanged();
};

} // namespace models

#endif // LISTITEM_H
