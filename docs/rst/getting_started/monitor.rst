.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _monitor_domain:

##############
Monitor Domain
##############

This application is able to track different :ref:`entities` that belong to the DDS communication protocol or
are, in some sense, related to it.
The DDS communication protocol (see |DDSSpecification|) divides a DDS network in independent
partitions referred to as :ref:`domain_entity`.
These Domains ensure that only entities in the same Domain can discover and communicate with each other,
which depends on the *Discovery Protocol* being used.
This application implements two different *Discovery Protocols* that could be used to monitor entities.

Several Domains could be monitored at the same time, and the :ref:`logical_entities` and the :ref:`dds_entities` under
any Domain would never be shared with others (except for the special case of the :ref:`locator_entity`).
This is not the case for the :ref:`physical_entities`, which can be shared between entities in different Domains.
Thus, the same :ref:`host_entity` or the same :ref:`locator_entity` could be related to entities in several Domains.

For the propose of monitoring a Domain, the application offers the button :ref:`init_monitor_button`, where a user can
manually specify the configuration of a Discovery type.
Once a Monitor is initialized in a specific Domain, the entities in this Domain will start to be discovered and their
data collected.
Every new entity or data discovered will be notified as a callback in the :ref:`issues_panel`.

.. note::

    Be aware that the discovery of the *Fast DDS Monitor* entities is made by DDS protocol,
    and so it will not be instantaneous or simultaneous.

.. _simple_discovery_monitor:

Simple Discovery Monitor
========================
The DDS Simple Discovery Protocol (SDP) relies on the discovery of individual entities through multicast communication.
No prior knowledge of the network or its architecture is required in order to create a new
monitor that connects with the *Participants* already running in the same network.
In order to configure this kind of Domain monitoring, only the number of the Domain that is
going to be tracked is needed.

.. _discovery_server_monitor:

Discovery Server Monitor
========================
The `Discovery Server <https://www.eprosima.com/index.php/products-all/tools/eprosima-discovery-server>`_
discovery protocol is a *Fast DDS* feature that centralizes the discovery phase in a single or a network of
*Discovery Servers*.
This has been demonstrated to be very useful in order to reduce the discovery traffic and to avoid certain problems
that could appear with the Simple Discovery Protocol and multicast.

In configure this type of Domain monitoring, a string with different
network addresses is required.
This string consists of one or several network addresses in the format of ``ip_address:port``, where each address
represents the IP-port pair where a Discovery Server is listening. Multiple network addresses are separated with
``;``. It is only necessary to connect successfully to one of the specified addresses, as interconnected Discovery
Servers create a redundant and robust network. However, connecting to all servers is not required.

The following command demonstrates how to connect to one Discovery Server in your own localhost
listening in port ``11811``, one in the same local network in address ``192.168.1.2:12000`` and a third
one in an external network in address ``8.8.8.8:12345``.

.. code-block:: console

    "127.0.0.1:11811;192.168.1.2:12000;8.8.8.8:12345"

In order to clarify how to set this parameter, please visit the
`Discovery Server CLI tutorial <https://fast-dds.docs.eprosima.com/en/latest/fastddscli/cli/cli.html#discovery>`_.
The parameter of the Discovery Server *Init New Monitor* button in this application will be used additionally as the
input to the CLI command.
