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
Additional options can be configured using the *Advanced Options* button (see :ref:`monitor_advanced_configuration`).

.. _monitor_advanced_configuration:

Advanced Options
----------------
*Fast DDS Monitor* allows configuring additional parameters using
the *Advanced Options* button in the *Initialize Monitor* dialog.

In case of enabling some of the supported advanced options, *OK* button will be enabled only if all inputs are correct,
so user must ensure of introducing the right values.

The list of supported advanced options is the following:

- **Easy Mode**:
  It allows the user to specify the IP address of the remote discovery server used in a
  `ROS 2 Easy Mode <https://docs.vulcanexus.org/en/latest/rst/enhancements/easy_mode/easy_mode.html>`_ scenario.
  In case of enabling this option, the user must introduce a valid IPv4 address in the text input.

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

.. _add_monitor_using_dds_xml_profiles:

DDS XML Profile configured Monitor
==================================

The *Fast DDS Monitor* allows users to configure and initialize monitoring using DDS XML profiles.
These profiles define the configuration of DDS entities, such as DomainParticipants, Topics, and QoS settings.

To add a monitor using DDS XML profiles, follow these steps:

1. **Prepare the XML Profiles File**:
   Create or edit an XML file that contains the configuration for the DDS entities.
   Ensure the file includes the necessary profiles for the DomainParticipants and other entities you want to monitor.
   Please refer to the `Fast DDS documentation <https://fast-dds.docs.eprosima.com/en/stable/fastdds/xml_configuration/xml_configuration.html>`_
   for details on how to structure the XML profiles.

2. **Load the XML Profiles File**:
    Click on the *File -> Initialize DDS Monitor with Profile* button in the *Fast DDS Monitor* application menu.

3. **Upload the XML File**:
   In the dialog that appears, select the XML file you prepared in step 1.
   The application will parse the file and load the profiles defined within it.

4. **Select the Profile**:
   After loading the XML file, you will see a list of available profiles.
   Choose the profile you want to use for monitoring.
