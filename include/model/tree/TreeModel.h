#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <json.hpp>

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

using json = nlohmann::json;

class TreeItem;

namespace models {

struct RecursiveStructType

{
    QString label;
    QList<RecursiveStructType> children;

    RecursiveStructType(
            QString label,
            QList<RecursiveStructType> children)
        : label(label)
        , children(children)
    {
    }

    RecursiveStructType(
            QString label)
        : label(label)
    {
    }

};


class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:

    enum TreeModelRoles
    {
        treeModelNameRole = Qt::UserRole + 1,
        treeModelValueRole
    };

    explicit TreeModel(
            const json& data,
            QObject* parent = 0);

    explicit TreeModel(
            QObject* parent = 0);

    ~TreeModel();

    QVariant data(
            const QModelIndex& index,
            int role) const Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(
            const QModelIndex& index) const Q_DECL_OVERRIDE;

    QModelIndex index(
            int row,
            int column,
            const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QModelIndex parent(
            const QModelIndex& index) const Q_DECL_OVERRIDE;

    int rowCount(
            const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

    int columnCount(
            const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

    void clear();

    void update(const json& data);

    QHash<int, QByteArray> roleNames() const override;

protected:

    void setupModelData(
            const json& data,
            TreeItem* parent);

private:

    TreeItem* rootItem_;
};

} // namespace models

#endif // TREEMODEL_H
