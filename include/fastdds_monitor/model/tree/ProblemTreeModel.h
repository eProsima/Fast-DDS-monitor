/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Maurizio Ingrassia
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_PROBLEMTREEMODEL_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_PROBLEMTREEMODEL_H

#include <fastdds_monitor/model/tree/ProblemTreeItem.h>

#include <QAbstractItemModel>

namespace models {

/*!
 * The Tree Model works as List Model, using one column and using the row information
 * referred to the parent node.
 */
class ProblemTreeModel : public QAbstractItemModel
{
    Q_OBJECT
    //Q_ENUMS(models::ProblemTreeItem::ModelItemRoles)

public:
    explicit ProblemTreeModel(
            QObject* parent = nullptr);

    ~ProblemTreeModel() override;

    // Overriden method from QAbstractItemModel

public:

    //! Role names to allow queries to get some specific information from the Item
    enum ModelItemRoles
    {
        idRole = Qt::UserRole + 1,      //! Role for attribute Id
        statusRole,                     //! Role for attribute Status
        valueRole,                      //! Role for attribute Value
        descriptionRole,                //! Role for attribute Description
        aliveRole,                      //! Role for attribute Alive
        nameRole                        //! Role for attribute Name
        // The nameRole must always be the last one as it is used in child classes
        // as the initial role of the enumeration)
    };

    int rowCount(
            const QModelIndex& index) const override;
    int columnCount(
            const QModelIndex& index) const override;

    QModelIndex index(
            int row,
            int column,
            const QModelIndex& parent) const override;

    QModelIndex parent(
            const QModelIndex& childIndex) const override;

    QVariant data(
            const QModelIndex& index,
            int role = 0) const override;

    bool setData(
            const QModelIndex& index,
            const QVariant& value,
            int role = Qt::EditRole) override;

    QHash<int, QByteArray> roleNames() const override;

public:
    //! Add an item to the top level.
    void addTopLevelItem(
            ProblemTreeItem* child);

    //! Add a child to the parent item.
    void addItem(
            ProblemTreeItem* parent,
            ProblemTreeItem* child);

    //! Remove the item from the model.
    void removeItem(
            ProblemTreeItem* item);

    //! Return the root item of the model.
    ProblemTreeItem* rootItem() const;

    //! Return the depth for the given index
    Q_INVOKABLE int depth(
            const QModelIndex& index) const;

    //! Clear the model.
    Q_INVOKABLE void clear();

    /*!
    *  Return the root item to the QML Side.
    *  This method is not meant to be used in client code.
    */
    Q_INVOKABLE QModelIndex rootIndex();

    // Check if top level item is defined
    bool containsTopLevelItem(
            ProblemTreeItem* child);

    // Check if item is defined in the parent item
    bool contains(
            ProblemTreeItem* parent,
            ProblemTreeItem* child);

    // Check if default empty value is the only element
    bool is_empty();

    void removeEmptyItem();

    //! Looks for a TopLevelItem that matches that id. If not existing, creates new one and returns it
    ProblemTreeItem*  getTopLevelItem(
            const backend::EntityId& id,
            const std::string& data,
            const bool& is_error,
            const std::string& description);

private:
    ProblemTreeItem* internalPointer(
            const QModelIndex& index) const;

private:
    ProblemTreeItem* root_item_;
    bool is_empty_;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_PROBLEMTREEMODEL_H
