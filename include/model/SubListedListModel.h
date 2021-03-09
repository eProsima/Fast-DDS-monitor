#ifndef SUBLISTEDLISTMODEL_H
#define SUBLISTEDLISTMODEL_H

#include <include/model/ListModel.h>
#include <include/model/SubListedListItem.h>

namespace models {

class SubListedListModel : public models::ListModel
{
    Q_OBJECT

public:

    /**
     * Constructor.
     */
    explicit SubListedListModel(
            models::SubListedListItem* prototype,
            QObject *parent = 0);

    /**
     * Returns the model contained by row item identified by a given item id.
     */
    Q_INVOKABLE QObject* subModelFromEntityId(
            QString entityId);
};

} // namespace models

#endif // SUBLISTEDLISTMODEL_H
