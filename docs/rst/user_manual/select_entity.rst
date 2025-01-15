.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _selected_entity:

###############
Selected Entity
###############

The application stores one entity as  **last entity clicked** in order to manage what information is displayed.
In the context of the Fast DDS Monitor, an entity is every element that can be tracked by the monitor
(see :ref:`entities`).
To set one entity as *clicked* double click in any entity in any of the :ref:`left_sidebar_layout` panels,
and this entity will be set as *Selected Entity* for the whole application from now on.
Selecting an entity has the following effects in the application view:

- The entity clicked will remain marked with blue background while no other entity is clicked or the Selected
  Entity is restored.
- In the :ref:`info_subpanel_layout`, the information related to this entity is displayed, such as *QoS* or specific
  entity settings.
- In the :ref:`statistics_panel_layout`, a general summary of the data stored for this entity is listed.
- If the selected entity is a Fast DDS Monitor entity belonging to the Physical or Logical Entities group,
  the entities displayed in :ref:`dds_panel` are only those *related* to this entity.
  Therefore, clicking one of the :ref:`dds_entities` does not update the :ref:`dds_panel`.
  To check the relation between entities please refer to the :ref:`entities` section.


Deselect Entity
---------------
To change the current *Selected Entity* just click in a another entity in the :ref:`left_sidebar_layout`.
Moreover, it is possible to deselect any entity. Use the *Refresh* button (:ref:`refresh_button`)
in order to preform that action.
Not having any entity selected has the following effects in the application view:

- The :ref:`dds_panel` will list all DDS entities present in any Domain monitored by Fast DDS Monitor,
  i.e. it will be possible to view any DomainParticipant, DataWriter and DataReader regardless of the physical entity
  or the DDS logical entity under which they are located.
- The information shown in the :ref:`info_panel_layout` becomes a brief summary of the current state of the application.
