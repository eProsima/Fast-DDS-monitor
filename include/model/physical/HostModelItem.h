#ifndef HOSTMODELITEM_H
#define HOSTMODELITEM_H

#include <include/model/EntityContainerModelItem.h>
#include <include/model/SubListedListItem.h>
#include <include/model/physical/UserModelItem.h>

namespace models {

class HostModelItem : public EntityContainerModelItem<UserModelItem, SubListedListModel>
{

public:

    using EntityContainerModelItem::EntityContainerModelItem;

};

}

#endif // HOSTMODELITEM_H
