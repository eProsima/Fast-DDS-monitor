.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_status_panel:
.. _pro_monitor_status_panel_layout:

##################
Status Panel |Pro|
##################

The status panel in the left sidebar displays data about the monitored entities and the current
state of the application.
It contains two sub-panels: :ref:`pro_status_panel_layout` and :ref:`pro_log_panel_layout`.
Click the sub-panel name to switch between them.

Drag the panel border to resize it.
To hide the panel, use **View → Hide Left Sidebar**.

.. _pro_status_panel_layout:

Status Sub-Panel
================

Displays a brief summary of the current state of *Fast DDS Monitor Pro*:

- **Entities**: the total number of entities currently being tracked.
- **Domains**: the list of domains initialized in the monitor so far.

.. figure:: /rst/figures/screenshots/status_panel_pro.png
    :align: center

.. _pro_log_panel:
.. _pro_log_panel_layout:

Log Sub-Panel
=============

Displays the events received by the application as *callbacks*.
Callbacks are triggered when new entities are discovered, when previously known entities change state,
or when any other event occurs in the monitored DDS network.
Each callback entry shows the affected entities and the time of the event.

.. figure:: /rst/figures/screenshots/log_panel_pro.png
    :align: center
