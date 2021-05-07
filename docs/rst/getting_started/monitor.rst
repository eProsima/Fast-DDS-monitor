.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _monitor_domain:

##############
Monitor Domain
##############

This application is able to track different :ref:`entities` that belongs to the DDS communication protocol or
are, in some sense, related to these entities.
The DDS communication protocol (see |DDSSpecification|) divide a DDS network in independent
partitions that are called :ref:`domain_entity`.
This Domains must fulfilled that only the entities in the same Domain can discover and communicate with each other,
and so this depends on the *Discovery Protocol* that is being use.
This application implements two different *Discovery Protocols* that could be use to monitor entities.

Several Domains could be monitored at the same time and the :ref:`logical_entities` and the :ref:`dds_entities` under
one Domain would never be shared between others (except for :ref:`locator_entity`).
This is not the case with the :ref:`physical_entities` that could be shared between entities in different domains, as
the same :ref:`host_entity`, or even the same :ref:`locator_entity` could be related with entities in several Domains.

For the propose of monitoring a Domain, the application gives the button :ref:`init_monitor_button` where a user can
manually specify the configuration of a Discovery type. |br|
Once a Monitor is initialized in a specific Domain, the entities in this Domain will start to be discovered and its
data collected.
Every new entity or data discovered will be notified as a callback in :ref:`issues_panel`.

.. note::

    Be aware that the discovery of the *Fast DDS Monitor* entities is made by DDS protocols,
    and so they will not be instantaneous or simultaneous.

.. _simple_discovery_monitor:

Simple Discovery Monitor
========================
The DDS Simple Discovery remains on the discovery of individual entities by multicast communication.
No previous information about the network and its architecture is needed in order to create a new
monitor that connects with the *Participants* already running in the same net. |br|
In order to configure this kind of Domain monitoring, it is only needed to specify the number of the Domain that is
going to be tracking.

.. _discovery_server_monitor:

Discovery Server Monitor
========================
The `Discovery Server <https://www.eprosima.com/index.php/products-all/tools/eprosima-discovery-server>`_
discovery protocol is a Fast DDS feature that allows to centralize the discovery phase in a single or a network of
*Discovery Servers*.
This has been demonstrated to be very useful in order to reduce the discovery traffic and to avoid certain problems
that could appear with the use of the Single Discovery and multicast.

In order to configure this kind of Domain monitoring, it is required to insert a string with different addresses.
This string consist in one or several addresses in the format of ``ip_address:port``, each of these are IP addresses
where a Discovery Server is listening.
Each address is separated with ``;``. |br|
It is only needed to successfully connect to one of the addresses set in the parameter, as a network of Discovery
Servers interconnected creates a redundancy that makes the network more robust, but it is not required to connect
with all of the Servers in it.

In the following snippet it is shown an example on how to connect with one Discovery Server in your own local host
listening in port ``11811``, one in the same local network in address ``192.168.1.2:12000`` and a third
one in an external network in address ``8.8.8.8:12345``.

.. code-block:: console

    "127.0.0.1:11811;192.168.1.2:12000;8.8.8.8:12345"

In order to clarify how to set this parameter, please visit the
`Discovery Server CLI tutorial <https://fast-dds.docs.eprosima.com/en/v2.3.0/fastddscli/cli/cli.html#discovery>`_.
The parameter of the Discovery Server *InitNewMonitor* in this app will be used equally as the input to the CLI command.

.. warning::
    Due to the designed architecture for the communication of the Monitor application and the DDS entities,
    it is highly recommended not to initialize a *Discovery Server Monitor* with Servers in different
    *Discovery Server Networks* (do not connect a monitor to servers that are not interconnected).

.. warning::
    Do not initialize a Discovery Server connection to a *Discovery Server Network* where you have already initialize
    a Monitor.
    This will lead to undefined behavior.
