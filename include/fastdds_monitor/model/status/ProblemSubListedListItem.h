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
 * @file ProblemSubListedListItem.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_STATUS_SUBLISTEDLISTITEM_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_STATUS_SUBLISTEDLISTITEM_H

#include <fastdds_monitor/backend/backend_types.h>
#include <fastdds_monitor/model/status/ProblemListItem.h>
#include <fastdds_monitor/model/status/ProblemListModel.h>

namespace models {

/**
 * @brief Abstract class that encapsulate the behaviour of entity Items that contains subentities
 *
 * Each Item represents a different \c Entity in the backend that has subentities.
 *
 * Implement the constructors for every Item with a backend \c EntityId .
 * Implement the functionality to manage the submodels and subitems.
 */
class ProblemSubListedListItem : public ProblemListItem
{
    Q_OBJECT

public:

    //! Default QObject constructor. Used for model specification
    ProblemSubListedListItem(
            QObject* parent = 0);

    //! Default QObject constructor. Used for model specification
    ProblemSubListedListItem(
            backend::EntityId id,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemSubListedListItem(
            backend::EntityId id,
            backend::ConnectionListSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemSubListedListItem(
            backend::EntityId id,
            backend::DeadlineMissedSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemSubListedListItem(
            backend::EntityId id,
            backend::IncompatibleQosSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemSubListedListItem(
            backend::EntityId id,
            backend::InconsistentTopicSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemSubListedListItem(
            backend::EntityId id,
            backend::LivelinessChangedSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemSubListedListItem(
            backend::EntityId id,
            backend::LivelinessLostSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemSubListedListItem(
            backend::EntityId id,
            backend::ProxySample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemSubListedListItem(
            backend::EntityId id,
            backend::SampleLostSample sample,
            QObject* parent = 0);

    //! Specific DDS Item constructor, with a backend \c EntityId associateds
    ProblemSubListedListItem(
            backend::EntityId id,
            backend::StatusesSizeSample sample,
            QObject* parent = 0);

    //! Clear and delete the subentities
    ~ProblemSubListedListItem()
    {
        if (subentities_list_model_)
        {
            subentities_list_model_->clear();
            delete subentities_list_model_;
        }
    }

    //! Return the submodel that contains the subentities of this item
    ProblemListModel* submodel()  const
    {
        return subentities_list_model_;
    }

protected:

    //! Submodule with subentities
    ProblemListModel* subentities_list_model_;
};

} // namespace models

#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_STATUS_SUBLISTEDLISTITEM_H
