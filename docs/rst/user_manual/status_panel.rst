.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _status_panel:

############
Status Panel
############

The left sidebar's status panel shows settings about the entities monitored by the application and some general
information about the state and the events of the monitor.

Status SubPanel
===============

This panel displays brief information of the current state of the *Fast DDS Monitor*,

* Entities
  * *Domains*: A list of the Domains that have been initialized in the Monitor so far.
  * *Entities*: Total number of entities that are being tracked.

.. _log_panel:

Log SubPanel
============

This panel displays the events that the application has received.
These events arise as *callbacks* that are generated because new entities have arrived to
the network or have been discovered, or because there has been any change in the DDS network state.
Each callback contains the entities discovered by the Monitor and the time it happened.
This list could be erased using :ref:`refresh_button`.
