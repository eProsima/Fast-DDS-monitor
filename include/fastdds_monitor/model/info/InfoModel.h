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
 * @file InfoModel.hpp
 */

#ifndef _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_INFOMODEL_H
#define _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_INFOMODEL_H

#include <fastdds_monitor/model/tree/TreeModel.h>

namespace models {

class InfoModel : public TreeModel
{
    Q_OBJECT

public:

    using TreeModel::TreeModel;

    //! Update the selected entity
    void update_selected_entity(
            QString entity_kind,
            QString entity_alias,
            QString entity_app_id);

signals:

    //! Signal to inform qml the alias of the entity selected.
    void entitySelected(
            QString entity_kind,
            QString entity_alias,
            QString entity_app_id);

};

} // namespace models


#endif // _EPROSIMA_FASTDDS_MONITOR_MODEL_TREE_TREEMODEL_H
