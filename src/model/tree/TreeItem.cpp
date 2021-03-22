#include <include/model/tree/TreeItem.h>

#include <QStringList>

TreeItem::TreeItem(
        const QList<QString>& data,
        TreeItem* parent)
{
    parentItem_ = parent;
    itemData_ = data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems_);
}

void TreeItem::appendChild(
        TreeItem* item)
{
    childItems_.append(item);
}

TreeItem* TreeItem::childItem(
        int row)
{
    return childItems_.value(row);
}

int TreeItem::childCount() const
{
    return childItems_.count();
}

int TreeItem::columnCount() const
{
    return itemData_.count();
}

QVariant TreeItem::data(int column) const
{
    return itemData_.value(column);
}

QVariant TreeItem::getItemName() const
{
    return itemData_.value(TreeItemData::NAME);
}

QVariant TreeItem::getItemValue() const
{
    return itemData_.value(TreeItemData::VALUE);
}

TreeItem* TreeItem::parentItem()
{
    return parentItem_;
}

void TreeItem::clear()
{
    qDeleteAll(childItems_);
    childItems_.clear();
}

int TreeItem::row() const
{
    if (parentItem_)
    {
        return parentItem_->childItems_.indexOf(const_cast<TreeItem*>(this));
    }

    return 0;
}
