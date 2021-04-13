#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <json.hpp>

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <include/model/tree/TreeItem.h>

using json = nlohmann::json;

namespace models {

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

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    TreeItem* get_item(
            const QModelIndex &index) const;

signals:
    void updatedData();

protected:

    void setup_model_data(
            const json& json_data,
            TreeItem* parent);

private:

    TreeItem* root_item_;

};

} // namespace models

#endif // TREEMODEL_H
