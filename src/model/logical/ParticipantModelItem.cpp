#include <iostream>

#include <include/model/logical/ParticipantModelItem.h>
#include <include/model/logical/EndpointModelItem.h>
#include <include/model/SubListedListModel.h>

ParticipantModelItem::ParticipantModelItem(QObject *parent)
    : SubListedListItem(parent)
{
    endpointListModel_ = new models::SubListedListModel(new EndpointModelItem());
}

ParticipantModelItem::ParticipantModelItem(
        QString guid,
        QString name,
        QObject *parent)
    : SubListedListItem(parent)
    , guid_(guid)
    , name_(name)
{
    endpointListModel_ = new models::SubListedListModel(new EndpointModelItem());
}

ParticipantModelItem::~ParticipantModelItem()
{
    endpointListModel_->clear();
    delete endpointListModel_;
}

QString ParticipantModelItem::entityId() const
{
    return guid_;
}

QVariant ParticipantModelItem::data(int role) const
{
    switch (role)
    {
        case participantGuid:
            return this->entityId();
        case participantNameRole:
            std::cout << "Request participantName" << std::endl;
            return this->name_;
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ParticipantModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles;

    roles[participantGuid] = "participantGuid";
    roles[participantNameRole] = "participantName";

    return roles;
}

models::ListModel* ParticipantModelItem::submodel() const
{
    return endpointListModel_;
}

