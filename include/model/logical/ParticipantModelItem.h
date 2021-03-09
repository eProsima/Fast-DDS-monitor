#ifndef PARTICIPANTMODELITEM_H
#define PARTICIPANTMODELITEM_H

#include <include/model/ListModel.h>
#include <include/model/SubListedListItem.h>

class ParticipantModelItem : public models::SubListedListItem
{
    Q_OBJECT

public:

    enum ParticipantModelItemRoles
    {
       participantGuid = Qt::UserRole + 1,
       participantNameRole
    };

    ParticipantModelItem(
            QString guid,
            QString name,
            QObject* parent = 0);

    ParticipantModelItem(
            QObject* parent = 0);

    ~ParticipantModelItem();

    QString entityId() const;

    QVariant data(
            int role) const;

    QHash<int, QByteArray> roleNames() const;

    models::ListModel* submodel()  const;

protected:

    QString guid_;
    QString name_;
    models::ListModel* endpointListModel_;
};

#endif
