#include <include/model/tree/TreeItem.h>
#include <include/model/tree/TreeModel.h>
#include <json.hpp>

#include <QStringList>

#include <iostream>

#include <QDebug>

using json = nlohmann::json;

namespace models {

TreeModel::TreeModel(
        const json& data,
        QObject* parent)
    : QAbstractItemModel(parent)
{
    rootItem_ = new TreeItem(QList<QString>() << "Name" << "Value");
    setupModelData(data, rootItem_);
}

TreeModel::TreeModel(
        QObject* parent)
    : QAbstractItemModel(parent)
{
    rootItem_ = new TreeItem(QList<QString>() << "Name" << "Value");
}


TreeModel::~TreeModel()
{
    beginResetModel();
    rootItem_->clear();
    endResetModel();
    delete rootItem_;
}

int TreeModel::columnCount(
        const QModelIndex& parent) const
{
    if (parent.isValid())
    {
        return getItem(parent)->columnCount();
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

    TreeItem* childItem = getItem(index);

    if (childItem != nullptr)
    {
        switch (role)
        {
            case treeModelNameRole:
                return childItem->getItemName();
            case treeModelValueRole:
                return childItem->getItemValue();
            default:
                return QVariant();
        }
    }

    return QVariant();
}

Qt::ItemFlags TreeModel::flags(
        const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
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

    TreeItem* parentItem = nullptr;
    TreeItem* childItem = nullptr;

    if (!index.isValid())
    {
        return QModelIndex();
    }

    if (parentItem == rootItem_)
    {
        return QModelIndex();
    }

    if ((childItem = getItem(index)) != nullptr)
    {
        if ((parentItem = childItem->parentItem()) != nullptr)
        {
            return createIndex(parentItem->row(), 0, parentItem);
        }
    }

    return QModelIndex();
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
        parentItem = getItem(parent);
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

TreeItem* TreeModel::getItem(
        const QModelIndex &index) const
{

    TreeItem* item = nullptr;

    if (index.isValid())
    {
        item = static_cast<TreeItem*>(index.internalPointer());
        if (item != nullptr)
        {
            return item;
        }
    }

    return rootItem_;
}

void TreeModel::setupModelData(
        const json& data,
        TreeItem* parent)
{
    QList<QString> qosData;

    bool lastChild = false;

    json value;

    for (json::const_iterator it = data.begin(); it != data.end(); ++it) {

        if (!data.is_array() || (data.is_array() && !it.value().is_primitive()) || it.value().is_array())
        {
            qosData << QString::fromUtf8(it.key().c_str());
        }

        if (it.value().size() == 1)
        {

            value = it.value().is_array() ? it.value().at(0) : it.value();

            if (value.is_string())
            {
                qosData << QString::fromUtf8(static_cast<std::string>(value).c_str());
                lastChild = true;
            }
            else if (value.is_number())
            {
                qosData << QString::number(static_cast<int>(value));
                lastChild = true;
            }
            else if (value.is_boolean())
            {
                qosData << (value ? QString("true") : QString("false"));
                lastChild = true;
            }
        }

        TreeItem* currentChild = new TreeItem(qosData, parent);
        parent->appendChild(currentChild);
        qosData.clear();

        if (!lastChild)
        {
            setupModelData(static_cast<json>(it.value()), currentChild);
        }

        lastChild = false;
    }
}

void TreeModel::clear()
{
    rootItem_->clear();
}

void TreeModel::update(const json& data)
{
    beginResetModel();
    clear();
    setupModelData(data, rootItem_);
    endResetModel();
    emit updatedData();
}

} // namespace models
