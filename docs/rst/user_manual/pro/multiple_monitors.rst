.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _multiple_monitors:

##############################
Multiple Monitor Support |Pro|
##############################

*Fast DDS Monitor Pro* lets you run several monitors at the same time within a single workspace. Each
monitor connects to its own DDS environment. You can freely
switch between them and open different panes of each monitor simultaneously, or add new ones at any time during a session.

The open-source edition of *Fast DDS Monitor* only supports one active monitor at a time. The Pro edition
removes that restriction, making it practical for deployments where more than one DDS environment needs to
be observed simultaneously.

.. _multiple_monitors_types:

Monitor Types
=============

When creating a new monitor, you choose one of three initialization modes:

* **DDS Domain** where the monitor joins a DDS Domain identified by its domain ID. Every DDS entity
  discovered in that domain, including participants, publishers, subscribers, and topics, becomes visible
  in the Explorer panels. See :ref:`initialize_monitoring` for the full procedure.

* **Discovery Server** where the monitor connects to a Discovery Server using a locator (address and port).
  Use this mode when the DDS network relies on the Discovery Server paradigm rather than Simple Discovery.

* **XML Profile** where the monitor reads its configuration from an XML profile file. This is useful when
  the DDS environment requires specific QoS policies or transport settings defined outside the application.

This is further explained in the section :ref:`monitor_domain`.

