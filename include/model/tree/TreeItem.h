#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>

class TreeItem
{
public:

    explicit TreeItem(
            const QList<QString>& data,
            TreeItem* parentItem = 0);

    ~TreeItem();

    void appendChild(
            TreeItem* child);

    TreeItem* childItem(
            int row);

    int childCount() const;

    int columnCount() const;

    QVariant data(
            int column) const;

    int row() const;

    TreeItem* parentItem();

    void clear();

private:

    QList<TreeItem*> childItems_;
    QList<QString> itemData_;
    TreeItem* parentItem_;
};

#endif // TREEITEM_H
