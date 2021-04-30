.. include:: ../exports/alias.include

.. _selected_entity:

###############
Selected Entity
###############

Functionality related with the entities displayed in :ref:`left_sidebar_layout`.

The application will store one entity as  **last entity clicked** in order to manage what information is displayed.
An entity is every element that is being tracked by the monitor (visit :ref:`entities` section).
To set one entity as *clicked* double click in any entity in any of the :ref:`left_sidebar_layout`,
and this entity will be set as *Selected Entity* for the whole application from now on.

The following information depends on the entity selected:

- In the :ref:`info_panel_layout` is displayed the information related to this entity, such as *QoS* or specific
  entity data.
- In the :ref:`statistics_panel_layout` is displayed a general summary of the data stored for this entity.
- In the :ref:`dds_panel` the entities displayed are just those that are *related* with the entity.
  To check the entities relations please refer to :ref:`entities` section. \
  Clicking one of the :ref:`dds_entities` do not update the :ref:`dds_panel`.

Deselect Entity
---------------
To change the actual *Selected Entity* just click in a another entity in the :ref:`left_sidebar_layout`.

To deselect any entity use the *Refresh* button (:ref:`refresh_button`).
This will cause the application to define as *Selected Entity* and abstract entity that represents all the entities
monitoring.
Thus, the information shown is a brief summary of the application actual state, and the
