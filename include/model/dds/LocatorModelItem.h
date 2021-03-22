#ifndef LOCATORMODELITEM_H
#define LOCATORMODELITEM_H

#include <include/model/ListItem.h>

namespace models {

class LocatorModelItem : public ListItem
{
    Q_OBJECT

public:

    LocatorModelItem(
            QObject *parent = 0)
        : ListItem(parent)
    {
    }

    LocatorModelItem(
            backend::EntityId id,
            QObject* parent = 0)
        : ListItem(id, parent)
    {
    }
};

}

#endif // LOCATORMODELITEM_H
