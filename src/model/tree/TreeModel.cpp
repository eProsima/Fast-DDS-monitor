#include <include/model/tree/TreeItem.h>
#include <include/model/tree/TreeModel.h>
#include <json.hpp>

#include <QStringList>

#include <iostream>

using json = nlohmann::json;

TreeModel::TreeModel(
        const json& data,
        QObject* parent)
    : QAbstractItemModel(parent)
{
    rootItem_ = new TreeItem(QList<QString>() << "Name" << "Value");
    setupModelData(data, rootItem_);
}

TreeModel::~TreeModel()
{
    delete rootItem_;
}

int TreeModel::columnCount(
        const QModelIndex& parent) const
{
    if (parent.isValid())
    {
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    }
    else
    {
        return rootItem_->columnCount();
    }
}

QVariant TreeModel::data(
        const QModelIndex& index,
        int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    switch (role)
    {
        case treeModelNameRole:
        case treeModelValueRole:
            return static_cast<TreeItem*>(index.internalPointer())->data(role - Qt::UserRole - 1);
        default:
            return QVariant();
    }
}

Qt::ItemFlags TreeModel::flags(
        const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    return QAbstractItemModel::flags(index);
}

QModelIndex TreeModel::index(
        int row,
        int column,
        const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    TreeItem* parentItem;

    if (!parent.isValid())
    {
        parentItem = rootItem_;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    TreeItem* childItem = parentItem->childItem(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex TreeModel::parent(
        const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem* parentItem = static_cast<TreeItem*>(index.internalPointer())->parentItem();

    if (parentItem == rootItem_)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex& parent) const
{
    TreeItem* parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
    {
        parentItem = rootItem_;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[treeModelNameRole] = "name";
    roles[treeModelValueRole] = "value";

    return roles;
}

void TreeModel::setupModelData(
        const json& data,
        TreeItem* parent)
{
    QList<QString> qosData;

    bool last_child = false;

    for (json::const_iterator it = data.begin(); it != data.end(); ++it) {

        qosData << QString::fromUtf8(it.key().c_str());

        if ((it.value().size() == 1) && (it.value().is_string()))
        {
            qosData << QString::fromUtf8(static_cast<std::string>(it.value()).c_str());
            last_child = true;
        }
        else
        {
            qosData << QString();
            last_child = false;
        }

        TreeItem* current_child = new TreeItem(qosData, parent);
        parent->appendChild(current_child);
        qosData.clear();

        if (!last_child) {
            this->setupModelData(static_cast<json>(it.value()), current_child);
        }
    }
}
