.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_status_panel:

############
Status Panel
############

The status panel in the left sidebar shows information about the entities being monitored and the
general state of the application.

Status Sub-Panel
================

Displays a brief summary of the current state of *Fast DDS Monitor Pro*:

* **Entities**

  * *Domains*: the list of domains initialized in the monitor so far.
  * *Entities*: the total number of entities currently being tracked.

.. _pro_log_panel:

Log Sub-Panel
=============

Displays the events received by the application as *callbacks*.
Callbacks are triggered when new entities are discovered, when previously known entities change state,
or when any other event occurs in the monitored DDS network.
Each callback entry shows the affected entities and the time of the event.
The list can be cleared using :ref:`pro_refresh_button`.
