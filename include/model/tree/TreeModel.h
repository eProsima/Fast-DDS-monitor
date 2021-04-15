// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file TreeModel.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_TREEMODEL_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_TREEMODEL_H


#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <include/backend/backend_types.h>
#include <include/model/tree/TreeItem.h>

using json = backend::EntityInfo;

namespace models {

/**
 * @brief Abstract class that encapsulate the behaviour of entity a Data Model in Tree format
 *
 * A \c TreeModel store and manage a \c TreeItem that is the parent node of a full tree of Items
 *
 * This Model is used by the view to represent values that contain values underneath
 * The representation of these trees by the view will use the name of each entity, and will show all their
 * subentities under this name, each represented by its own name.
 *
 * The construction of these models is made by Data in json format, where each key is going to be
 * used as a name, and the values below will be added in a new item in the tree under it
 * The last node (those without children nodes) is actually encapsulated in the father node in the \c VALUE column
 * inside its data.
 * This saves one node creation, and allows the view to represent in different columns those nodes with children
 * and the nodes that only represents a value
 */
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:

    //! Role names to allow queries to get some specific information from the Item
    enum TreeModelRoles
    {
        treeModelNameRole = Qt::UserRole + 1,   //! Role for attribute Name
        treeModelValueRole                      //! Role for attribute Value
    };

    /**
     *
     */
    explicit TreeModel(
            const json& data,
            QObject* parent = 0);

    explicit TreeModel(
            QObject* parent = 0);

    //! Delete and release all the information of items below
    ~TreeModel();

    //! Retrieve the data of one of the items indexed by \c index and its role \c role
    QVariant data(
            const QModelIndex& index,
            int role) const Q_DECL_OVERRIDE;

    //! Retrieve the flags of a node
    Qt::ItemFlags flags(
            const QModelIndex& index) const Q_DECL_OVERRIDE;

    //! Build an index giving row, column and parent
    QModelIndex index(
            int row,
            int column,
            const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

    //! Returns the index of the parend of the node indexed in \c index
    QModelIndex parent(
            const QModelIndex& index) const Q_DECL_OVERRIDE;

    //! Returns the number of rows in a node
    int rowCount(
            const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

    //! Returns the number of columns in a node
    int columnCount(
            const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

    //! Eliminates and release the parent node and all its children
    void clear();

    //! Clear the model and create a new tree with new data
    void update(const json& data);

    //! Return the role names of the values in nodes to acces them via \c data
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    //! Retrieve the item in the position \c index
    TreeItem* get_item(
            const QModelIndex &index) const;

signals:

    //! Signal that communicate that the model has been modified
    void updatedData();

protected:

    /**
     * @brief Fill an internal node with data in json format
     *
     * It iterates over a json object, each key is created as a new subnode and the values
     * are used to fill this subnode with this same function
     *
     * @param json_data data in json format to fill the item
     * @param parent item to fill
     */
    static void setup_model_data(
            const json& json_data,
            TreeItem* parent);

private:

    //! Parent node of the items tree
    TreeItem* root_item_;

};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_TREEMODEL_H
