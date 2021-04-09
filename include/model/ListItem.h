#ifndef LISTITEM_H
#define LISTITEM_H

#include <QObject>
#include <QVariant>
#include <QHash>

#include <include/backend/backend_types.h>
#include <include/backend/backend_utils.h>
#include <include/model/model_types.h>

namespace models
{

class ListModel;

// Class that represents:
//  an item in a list
class ListItem : public QObject
{
    Q_OBJECT

public :

    enum ModelItemRoles
    {
        idRole = Qt::UserRole + 1,
        nameRole
    };

    ListItem(
            QObject *parent = 0);

    ListItem(
            backend::EntityId id,
            QObject* parent = 0);

    ~ListItem();

    virtual EntityId entity_id() const;
    virtual QString name() const;
    virtual backend::EntityInfo info() const;

    backend::EntityId get_entity_id() const;

    virtual QVariant data(
            int role) const;

    virtual QHash<int, QByteArray> roleNames() const;

    virtual void triggerItemUpdate()
    {
        emit dataChanged();
    }

signals:

    void dataChanged();

protected:

    backend::EntityId id_;
    backend::EntityInfo info_;

};

} // namespace models

#endif // LISTITEM_H
