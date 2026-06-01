.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_selected_entity:

###############
Selected Entity
###############

The application tracks one entity as the **last entity clicked** to determine what information is
displayed throughout the interface.
In *Fast DDS Monitor Pro*, an entity is any element that can be tracked by the monitor
(see :ref:`entities`).

To set an entity as selected, double-click it in any of the :ref:`pro_left_sidebar_layout` panels.
The selected entity is then used as the context for the whole application.

Selecting an entity has the following effects:

- The entity is highlighted with a blue background until a different entity is selected or the
  selection is cleared.
- The :ref:`pro_info_subpanel_layout` displays the information for that entity,
  such as its *QoS* settings or specific entity properties.
- The :ref:`pro_statistics_panel_layout` shows a statistical summary of the data stored for that entity.
- If the selected entity is a Physical or Logical entity, the :ref:`pro_dds_panel_layout` shows only
  the DDS entities related to it.
  Clicking a :ref:`dds_entities` entry in that state does not update the DDS panel.
  See :ref:`entities` for details on entity relationships.

Deselect Entity
===============

To change the selected entity, double-click a different entity in the :ref:`pro_left_sidebar_layout`.
To clear the selection entirely, use the **Refresh** button (:ref:`pro_refresh_button`).

When no entity is selected:

- The :ref:`pro_dds_panel_layout` lists all DDS entities across every monitored domain,
  showing all DomainParticipants, DataWriters, and DataReaders regardless of their physical or logical
  context.
- The :ref:`pro_info_panel_layout` shows a brief summary of the overall application state.
