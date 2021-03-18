#include <include/model/tree/TreeItem.h>
#include <include/model/tree/TreeModel.h>
#include <json.hpp>

#include <QStringList>

#include <iostream>

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

        TreeItem* current_child = new TreeItem(qosData, parent);
        parent->appendChild(current_child);
        qosData.clear();

        if (!lastChild)
        {
            setupModelData(static_cast<json>(it.value()), current_child);
        }

        lastChild = false;
    }
}

void TreeModel::clear()
{
    beginResetModel();
    rootItem_->clear();
    endResetModel();
}

void TreeModel::update(const json& data)
{
    clear();
    setupModelData(data, rootItem_);

    // re draw info
    // emit dataChanged(0, 0);
}

} // namespace models
