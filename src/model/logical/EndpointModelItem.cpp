#include <iostream>

#include <include/model/logical/EndpointModelItem.h>
#include <include/model/logical/TopicModelItem.h>

EndpointModelItem::EndpointModelItem(
        QObject *parent)
    : SubListedListItem(parent)
{
    topicListModel_ = new models::ListModel(new TopicModelItem());
}

EndpointModelItem::EndpointModelItem(
        QString guid,
        QString type,
        QObject *parent)
    : SubListedListItem(parent)
    , guid_(guid)
    , type_(type)
{
    topicListModel_ = new models::ListModel(new TopicModelItem());
}

EndpointModelItem::~EndpointModelItem()
{
    topicListModel_->clear();
    delete topicListModel_;
}

QString EndpointModelItem::entityId() const
{
    return guid_;
}

QVariant EndpointModelItem::data(
        int role) const
{
   switch (role)
   {
       case endpointGuidRole:
           return this->entityId();
       case endpointTypeRole:
           return this->type_;
       default:
           return QVariant();
   }
}

QHash<int, QByteArray> EndpointModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles;

    roles[endpointGuidRole] = "endpointGuid";
    roles[endpointTypeRole] = "endpointType";

    return roles;
}

models::ListModel* EndpointModelItem::submodel() const
{
    return topicListModel_;
}

