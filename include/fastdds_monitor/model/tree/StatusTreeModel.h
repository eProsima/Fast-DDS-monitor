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

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_StatusTreeModel_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_StatusTreeModel_H

#include <fastdds_monitor/model/tree/StatusTreeItem.h>

#include <QAbstractItemModel>

namespace models {

/*!
 * The Tree Model works as List Model, using one column and using the row information
 * referred to the parent node.
 */
class StatusTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit StatusTreeModel(
            QObject* parent = nullptr);

    ~StatusTreeModel() override;

    // Overriden method from QAbstractItemModel

public:
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

    Q_INVOKABLE QVariant name(
            const QModelIndex& index,
            int role = 0) const;

    Q_INVOKABLE QVariant id(
            const QModelIndex& index,
            int role = 0) const;

    Q_INVOKABLE QVariant status(
            const QModelIndex& index,
            int role = 0) const;

    Q_INVOKABLE QVariant kind(
            const QModelIndex& index,
            int role = 0) const;

    Q_INVOKABLE QVariant value(
            const QModelIndex& index,
            int role = 0) const;

    Q_INVOKABLE QVariant description(
            const QModelIndex& index,
            int role = 0) const;

    Q_INVOKABLE QVariant alive(
            const QModelIndex& index,
            int role = 0) const;

    bool setData(
            const QModelIndex& index,
            const QVariant& value,
            int role = Qt::EditRole) override;

    bool removeRow(
            int row,
            const QModelIndex &index = QModelIndex());

public:
    //! Add an item to the top level.
    void addTopLevelItem(
            StatusTreeItem* child);

    //! Add a child to the parent item.
    void addItem(
            StatusTreeItem* parent,
            StatusTreeItem* child);

    //! Remove the item from the model.
    void removeItem(
            StatusTreeItem* item);

    //! Return the root item of the model.
    StatusTreeItem* rootItem() const;

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
            StatusTreeItem* child);

    // Check if item is defined in the parent item
    bool contains(
            StatusTreeItem* parent,
            StatusTreeItem* child);

    // Returns the child in the given position
    StatusTreeItem* child(
            int row);

    // Check if default empty value is the only element
    bool is_empty();

    void removeEmptyItem();

    //! Looks for a TopLevelItem that matches that id. If not existing, creates new one and returns it
    StatusTreeItem*  getTopLevelItem(
            const backend::EntityId& id,
            const std::string& data,
            const bool& is_error,
            const std::string& description);

    void set_source_model(
            StatusTreeModel* source_model);

    /*!
    *  Filters the model if it is defined as proxy
    */
    Q_INVOKABLE void filter_proxy(
            const QVariant& entity_id);

private:
    StatusTreeItem* internalPointer(
            const QModelIndex& index) const;

    StatusTreeItem* copy(
            StatusTreeItem* source,
            const backend::EntityId entity_id);

    void filter(
            const backend::EntityId entity_id);

private:
    StatusTreeModel* source_model_;
    StatusTreeItem* root_item_;
    bool is_empty_;

    backend::EntityId current_filter_;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_StatusTreeModel_H
