#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QList>
#include <QHash>
#include <QByteArray>
#include <QtAlgorithms>
#include <QQmlEngine>

#include <include/model/ListItem.h>
#include <include/backend/backend_types.h>

namespace models {

class ListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:

    /**
     * Constructor.
     */
    explicit ListModel(
            ListItem* prototype,
            QObject* parent = 0);

    /**
     * Destructor.
     */
    ~ListModel();

    /**
     * Returns the number of rows under the given parent.
     * When the parent is valid it means that rowCount is returning the number of children of parent.
     */
    int rowCount(
            const QModelIndex& parent = QModelIndex()) const;

    /**
     * Returns the data stored under the given role for the item referred to by the index.
     */
    QVariant data(
            const QModelIndex& index,
            int role) const;

    /**
     * Returns the model's role names.
     */
    QHash<int, QByteArray> roleNames() const;

    /**
     * This function provides a convenient way to append a single new item.
     */
    void appendRow(
            ListItem* item);

    /**
     * Appends several items to the Model.
     */
    void appendRows(
            QList<ListItem*>& items);

    /**
     * Inserts a single row before the given row in the child items of the parent specified.
     */
    void insertRow(
            int row,
            ListItem* item);

    /**
     * Removes a single row at the position given by row.
     * Returns true if the row was removed, and false if the row was not found or is not valid.
     */
    bool removeRow(
            int row,
            const QModelIndex& index = QModelIndex());

    /**
     * Removes several rows starting at position given by row until either count or the model's last row is reached.
     * Returns true if the rows were removed, false if the given initial row was not fount or is not invalid.
     */
    bool removeRows(
            int row,
            int count,
            const QModelIndex& index = QModelIndex());

    /**
     * Returns the item whose id matches the itemId.
     */
    ListItem* find(
            EntityId itemId) const;

    /**
     * Returns the row index of item in the model.
     */
    int getRowFromItem(
            ListItem* item) const;

    /**
     * Returns the index of the row in the model containing the item.
     */
    QModelIndex indexFromItem(
            ListItem* item) const;

    /**
     * Returns a QList containing the items of the model.
     */
    QList<ListItem*> toList() const;

    /**
     * Returns a QVariant containg the data of the row item at a given index in the model.
     */
    Q_INVOKABLE QVariant get(
            int index);

    /**
     * Returns the row index of an item given the item id.
     */
    Q_INVOKABLE int rowIndexFromId(
            EntityId itemId);

    /**
     * Clears the whole model removing all rows.
     */
    Q_INVOKABLE void clear();

protected:

    ListItem* prototype_;
    QList<ListItem*> items_;

private slots:

    /**
     * Slot triggered when a row item needs to be updated to reflect data changes.
     */
    void updateItem();

signals:

    void countChanged(
            int count);
};

} // namespace models

#endif // LISTMODEL_H
