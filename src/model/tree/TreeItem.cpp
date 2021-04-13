#include <include/model/tree/TreeItem.h>

#include <QStringList>

namespace models {

TreeItem::TreeItem(
        const QList<QString>& data,
        TreeItem* parent)
{
    parent_item_ = parent;
    item_data_ = data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(child_items_);
}

void TreeItem::append_child(
        TreeItem* item)
{
    child_items_.append(item);
}

TreeItem* TreeItem::child_item(
        int row)
{
    return child_items_.value(row);
}

int TreeItem::child_count() const
{
    return child_items_.count();
}

int TreeItem::column_count() const
{
    return item_data_.count();
}

QVariant TreeItem::data(int column) const
{
    return item_data_.value(column);
}

QVariant TreeItem::get_item_name() const
{
    return item_data_.value(TreeItemData::NAME);
}

QVariant TreeItem::get_item_value() const
{
    return item_data_.value(TreeItemData::VALUE);
}

QString TreeItem::name() const
{
    return get_item_name().toString();
}

TreeItem* TreeItem::parent_item()
{
    return parent_item_;
}

void TreeItem::clear()
{
    qDeleteAll(child_items_);
    child_items_.clear();
}

int TreeItem::row() const
{
    if (parent_item_)
    {
        return parent_item_->child_items_.indexOf(const_cast<TreeItem*>(this));
    }

    return 0;
}

TreeItem* TreeItem::find(QString key) const
{
    for (auto item : child_items_)
    {
        if (item->name() == key)
        {
            return item;
        }

        // Recursive search
        TreeItem* child_item = item->find(key);
        if (child_item != nullptr)
        {
            return child_item;
        }
    }
    return nullptr;
}

} // namespace models

