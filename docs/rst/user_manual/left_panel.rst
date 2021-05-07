.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _left_panel:

############
Left Sidebar
############

The left sidebar shows the various entities that the application has information about,
i.e. the entities that the monitor has discovered.
It is recommended to check the section :ref:`entities` in order to get a better approach on the kind of entities
that are displayed and the connection between them.

.. _dds_panel:

DDS Panel
=========
In this panel are displayed all the :ref:`dds_entities` that has been discovered by the monitor so far under every
DDS domain or Discovery Server monitored.
This panel displays specific DDS entities related with the Fast DDS Monitor entity currently selected
(see :ref:`selected_entity`). |br|
For example, it is possible to track the DDS entities created from an application running on a specific *Host*,
*User*, or *Process*, as well as the DDS entities that are working on a specific DDS domain or are publishing or
subscribed to a given topic. |br|
Every entity in this panel is interactive:

- Clicking in the Participant name or the Participant icon will expand or collapse the list of DataWriters/DataReaders
  of that Participant.
- Clicking in the DataReader/DataWriter name or the DataReader/DataWriter icon will expand
  or collapse the list of Locators of that DataReader/DataWriter.
- Double clicking in an entity will set this entity as *selected*.
  Please refer to :ref:`selected_entity` for more information on what it means for an entity to be selected.

.. _physical_panel:

Physical Panel
==============
This panel displays all the :ref:`physical_entities` that the monitor has discovered so far.
Similar to the :ref:`dds_panel`, every entity in this panel is interactive:

- Clicking in the Host name or the Host icon will expand or collapse the list of Users of the Host.
- Clicking in the User name or the User icon will expand or collapse the list of Processes of the User.
- Double clicking in an entity will set this entity as *selected*.
  Please refer to :ref:`selected_entity` for more information on what it means for an entity to be selected.

.. _logical_panel:

Logical Panel
=============
This panel displays all the :ref:`logical_entities` that are being monitored.
he DDS domains that Fast DDS Monitor is monitoring are the ones set by the user (see :ref:`monitor_domain`)
and no new domains will or could be discovered apart from them since the Domains could not be discovered,
but known beforehand.
Therefore, this panel will only update the information. |br|
For example, having enabled the monitoring of Domain X,
if an application using Fast DDS creates a new DomainParticipant in that domain with a DataWriter publishing in
Topic Y, the information of that topic will appear in this view listed under Domain X to which
the DomainParticipant discovered by the monitor belongs.

Similar to the :ref:`dds_panel`, every entity in this panel is interactive:

- Clicking in the Domain name or the Domain icon will expand or collapse the list of Topics of the Domain.
- Double clicking in an entity will set this entity as *selected*.
  Please refer to :ref:`selected_entity` for more information on what it means for an entity to be selected.
