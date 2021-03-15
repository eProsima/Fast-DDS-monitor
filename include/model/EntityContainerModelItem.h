#ifndef ENTITYCONTAINERMODELITEM_H
#define ENTITYCONTAINERMODELITEM_H

#include <QObject>
#include <QVariant>
#include <QHash>

#include <include/model/SubListedListModel.h>
#include <include/model/SubListedListItem.h>

#include <include/model/ListItem.h>
#include <include/backend/backend_types.h>
#include <include/backend/backend_utils.h>
#include <include/model/model_types.h>

namespace models
{

template<class SubEntityClass, class SubEntityModelClass>
class EntityContainerModelItem : public SubListedListItem
{
public :

    EntityContainerModelItem(
            QObject *parent = 0)
        : SubListedListItem(parent)
    {
        subEntitiesListModel_ = new SubEntityModelClass(new SubEntityClass());
    }

    EntityContainerModelItem(
            backend::EntityId id,
            QObject* parent = 0)
        : SubListedListItem(id, parent)
    {
        subEntitiesListModel_ = new SubEntityModelClass(new SubEntityClass());
    }

};

} // namespace models

#endif // ENTITYCONTAINERMODELITEM_H
