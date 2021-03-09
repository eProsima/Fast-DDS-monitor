#ifndef SUBLISTEDLISTITEM_H
#define SUBLISTEDLISTITEM_H

#include "ListItem.h"


namespace models {

class ListModel;

class SubListedListItem : public models::ListItem
{
    Q_OBJECT

public:

    SubListedListItem(
            QObject *parent = 0)
        : models::ListItem(parent)
    {
    }

    virtual ~SubListedListItem()
    {
    }

    virtual models::ListModel*  submodel()  const = 0;
};

} // namespace models

#endif // SUBLISTEDLISTITEM_H
