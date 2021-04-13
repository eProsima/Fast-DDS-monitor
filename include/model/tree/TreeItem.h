#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>

namespace models {

class TreeItem
{
public:

    enum TreeItemData
    {
        NAME,
        VALUE
    };

    explicit TreeItem(
            const QList<QString>& data,
            TreeItem* parent_item = 0);

    ~TreeItem();

    void append_child(
            TreeItem* child);

    TreeItem* child_item(
            int row);

    int child_count() const;

    int column_count() const;

    QVariant data(
            int column) const;

    QVariant get_item_name() const;

    QVariant get_item_value() const;

    int row() const;

    TreeItem* parent_item();

    void clear();

private:

    QList<TreeItem*> child_items_;
    QList<QString> item_data_;
    TreeItem* parent_item_;
};

} // namespace models

#endif // TREEITEM_H
