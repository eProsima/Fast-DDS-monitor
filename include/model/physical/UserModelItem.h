#ifndef USERMODELITEM_H
#define USERMODELITEM_H

#include <include/model/EntityContainerModelItem.h>
#include <include/model/physical/ProcessModelItem.h>

namespace models {

class UserModelItem : public EntityContainerModelItem<ProcessModelItem, ListModel>
{

public:

    using EntityContainerModelItem::EntityContainerModelItem;

};

}

#endif
