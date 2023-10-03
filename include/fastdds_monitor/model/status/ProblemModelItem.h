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

/**
 * @file ProblemModelItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_STATUS_PROBLEMMODELITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_STATUS_PROBLEMMODELITEM_H

#include <fastdds_monitor/model/status/ProblemListItem.h>

namespace models {


/**
 * @brief Class that represents an Problem Item in the Problem Model
 */
class ProblemModelItem : public ProblemListItem
{
    Q_OBJECT

public:

    //! Add new roles only for Problem items
    enum ProblemModelItemRoles
    {
        typeRole = ModelItemRoles::nameRole + 1,    //! Role for attribute Type
    };

    //! Default QObject constructor. Used for model specification
    ProblemModelItem(
            QObject* parent = 0);

    //! Default QObject constructor. Used for model specification
    ProblemModelItem(
            backend::EntityId id,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemModelItem(
            backend::EntityId id,
            backend::ConnectionListSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemModelItem(
            backend::EntityId id,
            backend::DeadlineMissedSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemModelItem(
            backend::EntityId id,
            backend::IncompatibleQosSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemModelItem(
            backend::EntityId id,
            backend::InconsistentTopicSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemModelItem(
            backend::EntityId id,
            backend::LivelinessChangedSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemModelItem(
            backend::EntityId id,
            backend::LivelinessLostSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemModelItem(
            backend::EntityId id,
            backend::ProxySample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemModelItem(
            backend::EntityId id,
            backend::SampleLostSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemModelItem(
            backend::EntityId id,
            backend::StatusesSizeSample sample,
            QObject* parent = 0);

    //! Override the ProblemListItem \c data method to add new roles
    QVariant data(
            int role) const override;

    //! Getter for type attribute
    QString type() const;

    //! Override the ProblemListItem \c roleNames method to add new roles
    QHash<int, QByteArray> roleNames() const override;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_STATUS_PROBLEMMODELITEM_H
