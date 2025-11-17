// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Monitor.
//
// eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

/**
 * @file TreeModel.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_TREEMODEL_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_TREEMODEL_H

#include <mutex>

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/model/tree/TreeItem.h>

using json = backend::EntityInfo;
using ordered_json = nlohmann::ordered_json;

namespace models {

/**
 * @brief Abstract class that encapsulate the behaviour of entity a Data Model in Tree format
 *
 * A \c TreeModel store and manage a \c TreeItem that is the parent node of a full tree of Items.
 *
 * This Model is used by the view to represent values that contain values underneath.
 * The representation of these trees by the view will use the name of each entity, and will show all their
 * subentities under this name, each represented by its own name.
 *
 * The construction of these models is made by Data in json format, where each key is going to be
 * used as a name, and the values below will be added in a new item in the tree under it.
 * The last node (those without children nodes) is actually encapsulated in the father node in the \c VALUE column
 * inside its data.
 * This saves one node creation, and allows the view to represent in different columns those nodes with children
 * and the nodes that only represents a value.
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
    void update(
            json data);

    //! Update the tree with new data without cleaning the entire model
    void update_without_clean(
            ordered_json& data);

    //! Return the role names of the values in nodes to acces them via \c data
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    //! Retrieve the item in the position \c index
    TreeItem* get_item(
            const QModelIndex& index) const;

    // Return the value of the name role
    Q_INVOKABLE
    int nameRole() const
    {
        return TreeModelRoles::treeModelNameRole;
    }

    // Return the value of the value role
    Q_INVOKABLE
    int valueRole() const
    {
        return TreeModelRoles::treeModelValueRole;
    }

    // Copy the current data in json format to clipboard
    Q_INVOKABLE
    void copy_json_to_clipboard() const;

signals:

    //! Signal that communicate that the model has been modified
    void updatedData();

protected:

    /**
     * @brief Fill an internal node with data in json format
     *
     * It iterates over a json object, each key is created as a new subnode and the values
     * are used to fill this subnode with this same function.
     *
     * Go through the whole json and its subelements and change every array of elements by a dictionary
     * indexed by numbers starting in 0.
     * For the first element, adds an empty row at the end to prevent the TreeView(*) error.
     *
     * (*) TreeView does not collapse correctly a subtree in case its last element is itself a subtree and
     * it is not collapsed.
     * @param json_data data in json format to fill the item
     * @param parent item to fill
     * @param _first wether is the parent element of the json (false only used in internal recursion)
     */
    static void setup_model_data(
            const json& json_data,
            TreeItem* parent,
            bool _first = true);

    /**
     * @brief Recursive function that fills an internal node with data in json format without
     * cleaning the entire model.
     *
     * @param parent Item from which the update is performed
     * @param parent_index Index of the parent in the TreeModel
     * @param json_data Data with the new version of the tree
     */
    void setup_model_data_without_clean(
            TreeItem* parent,
            const QModelIndex& parent_index,
            const ordered_json& json_data);

    /**
     * @brief Iterates over the children of a node to find one with a specific name
     * @param parent parent node where to search
     * @param name name of the child node to search
     * @return pointer to the child node if found, nullptr otherwise
     */
    TreeItem* find_child_by_name(
            TreeItem* parent,
            const QString& name) const;

    /**
     * @brief Helper method to return an invalid QModelIndex to QML
     * @return An invalid QModelIndex
     */
    Q_INVOKABLE QModelIndex invalidIndex() const
    {
        return QModelIndex();
    }

private:

    //! Parent node of the items tree
    TreeItem* root_item_;

    mutable std::mutex update_mutex_;

    // Local copy of the last inserted data to allow copy to clipboard
    ordered_json data_to_copy_;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_TREEMODEL_H
