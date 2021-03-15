#ifndef DOMAINMODELITEM_H
#define DOMAINMODELITEM_H

#include <include/model/EntityContainerModelItem.h>
#include <include/model/ListModel.h>
#include <include/model/logical/TopicModelItem.h>

namespace models {

class DomainModelItem : public EntityContainerModelItem<TopicModelItem, ListModel>
{

public:

    using EntityContainerModelItem::EntityContainerModelItem;

};

}

#endif // DOMAINMODELITEM_H
