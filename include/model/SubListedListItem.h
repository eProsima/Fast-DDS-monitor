#ifndef SUBLISTEDLISTITEM_H
#define SUBLISTEDLISTITEM_H

#include <include/model/ListItem.h>
#include <include/model/ListModel.h>
#include <include/backend/backend_types.h>
namespace models {

// Class that represents:
//  an item in a list
//  it has subentities that are items
class SubListedListItem : public ListItem
{
    Q_OBJECT

public:

    SubListedListItem(
            QObject *parent = 0)
        : ListItem(parent)
    {
    }

    SubListedListItem(
            backend::EntityId id,
            QObject* parent = 0)
        : ListItem(id, parent)
    {
    }

    ~SubListedListItem()
    {
        subEntitiesListModel_->clear();
        delete subEntitiesListModel_;
    }

    ListModel* submodel()  const
    {
        return subEntitiesListModel_;
    }

protected:

    ListModel* subEntitiesListModel_;
};

} // namespace models

#endif // SUBLISTEDLISTITEM_H
