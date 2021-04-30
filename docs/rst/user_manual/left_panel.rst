.. include:: ../exports/alias.include

.. _left_panel:

##########
Left Panel
##########

Functionality related with :ref:`left_sidebar_layout`.

In this left panels are displayed the different entities that the application has information from.
It is recommended to check the section :ref:`entities` in order to get a better approach on the kind of entities
that are displayed, the relation between a DDS execution, and the connection between them.

.. _dds_panel:

DDS Panel
=========
In this panel are displayed all the :ref:`dds_entities` that has been discovered so far under every domain monitored.
This panel displays specific entities related with the Entity currently selected (refer to :ref:`selected_entity`).

Every entity in this panel is interactive:

- Clicking in the Participant name or the Participant icon will expand or collapse the list of Endpoints of the
  Participant.
- Clicking in the Endpoint name or the Endpoint icon will expand or collapse the list of Locators of the Endpoint.
- Double clicking in an Entity will set this entity as *selected*. For more information refer to :ref:`selected_entity`

.. _physical_panel:

Physical Panel
==============
In this panel are displayed all the :ref:`physical_entities` that has been discovered so far.
The domains that are being monitor are the ones set by the user (visit :ref:`monitor_domain`) and no new domains
will or could be discovered apart from them, because DDS specification says that Domains could not be discovered, but
known beforehand.
Therefore, the information discovered that will be displayed here would be the different Topics that are created
under each specific domain.

Similar to the :ref:`dds_panel`, every entity in this panel is interactive:

- Clicking in the Host name or the Host icon will expand or collapse the list of Users of the Host.
- Clicking in the User name or the User icon will expand or collapse the list of Processes of the User.
- Double clicking in an Entity will set this entity as *selected*. For more information refer to :ref:`selected_entity`

.. _logical_panel:

Logical Panel
=============
In this panel are displayed all the :ref:`logical_entities` that are being monitored.
The domains that are being monitor are the ones set by the user (visit :ref:`monitor_domain`) and no new domains
will or could be discovered apart from them, because DDS specification says that Domains could not be discovered, but
known beforehand.
Therefore, the information discovered that will be displayed here would be the different Topics that are created
under each specific domain.

Similar to the :ref:`dds_panel`, every entity in this panel is interactive:

- Clicking in the Domain name or the Domain icon will expand or collapse the list of Topics of the Domain.
- Double clicking in an Entity will set this entity as *selected*. For more information refer to :ref:`selected_entity`.
