.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_left_panel:

##############
Explorer Panel
##############

The left sidebar displays all entities known to the application along with their available information.
It is recommended to read the :ref:`entities` section for an overview of the entity types and
their relationships before using this panel.

.. _pro_dds_panel:

DDS Panel
=========

This panel displays all :ref:`dds_entities` discovered by the monitor across every DDS domain or
Discovery Server being monitored.
The list is filtered to show only the DDS entities related to the currently selected entity
(see :ref:`pro_selected_entity`).
For example, selecting a specific *Host*, *User*, or *Process* shows only the DDS entities running
on that physical context.

Every entity in this panel is interactive:

- Click the Participant name or icon to expand or collapse its DataWriters and DataReaders.
- Click a DataReader or DataWriter name or icon to expand or collapse its Locators.
- Double-click an entity to set it as the *selected entity*.
  See :ref:`pro_selected_entity` for details.

.. _pro_physical_panel:

Physical Panel
==============

This panel displays all :ref:`physical_entities` discovered by the monitor: *Host*, *User*, and *Process*.
Every entity is interactive:

- Click a Host name or icon to expand or collapse its Users.
- Click a User name or icon to expand or collapse its Processes.
- Double-click an entity to set it as the *selected entity*.
  See :ref:`pro_selected_entity` for details.

.. _pro_logical_panel:

Logical Panel
=============

This panel displays all :ref:`logical_entities` being monitored: *Domain* and *Topic*.
Domains are explicitly configured by the user (see :ref:`monitor_domain`); they cannot be discovered
automatically.
For example, after enabling monitoring of Domain X, any new *DomainParticipant* created in that domain —
along with its DataWriters and their topics — will appear in this panel under Domain X.

Every entity is interactive:

- Click a Domain name or icon to expand or collapse its Topics.
- Double-click an entity to set it as the *selected entity*.
  See :ref:`pro_selected_entity` for details.

.. _pro_info_panel:

Info Panel
==========

This panel displays information about the currently selected entity (see :ref:`pro_selected_entity`).
Some fields are common to all entity types; others are specific to each type:

* **Common fields**

  * **name**: internal name of the entity
  * **id**: internal unique identifier
  * **kind**: entity type (e.g. host)
  * **alive**: whether the entity is currently alive
  * **alias**: user-assigned alias
  * **metatraffic**: whether the entity processes metatraffic data
  * **status**: current status of the entity
  * **discovery_source**: how the entity was discovered (``discovery`` for DDS discovery protocol,
    ``proxy`` for discovery through statistics messages)

* **Process**

  * **pid**: process ID on its host

* **Topic**

  * **type_name**: name of the topic's data type

* **Domain**

  * **domain_id**: the DDS domain ID

* **Participant**

  * **GUID**: DDS GUID
  * **QoS**: DDS QoS configuration

* **DataWriter**

  * **GUID**: DDS GUID
  * **QoS**: DDS QoS configuration

* **DataReader**

  * **GUID**: DDS GUID
  * **QoS**: DDS QoS configuration

.. _pro_statistics_panel:

Statistics Panel
================

This panel shows a summary of statistical data for the currently selected entity
(see :ref:`pro_selected_entity`).
Data is aggregated across all entities related to the selected one, using a single bin spanning
all available data.
When no entity is selected, the summary covers all entities in the application.

.. list-table::
    :header-rows: 1

    *   - Data Kind
        - Statistic Kind
        - Description
    *   - ``FASTDDS_LATENCY``
        - ``MEDIAN``
        - Median application latency
    *   - ``FASTDDS_LATENCY``
        - ``STANDARD_DEVIATION``
        - Standard deviation of application latency
    *   - ``PUBLICATION_THROUGHPUT``
        - ``MEDIAN``
        - Median publication throughput
    *   - ``PUBLICATION_THROUGHPUT``
        - ``STANDARD_DEVIATION``
        - Standard deviation of publication throughput
    *   - ``SUBSCRIPTION_THROUGHPUT``
        - ``MEDIAN``
        - Median subscription throughput
    *   - ``SUBSCRIPTION_THROUGHPUT``
        - ``STANDARD_DEVIATION``
        - Standard deviation of subscription throughput
    *   - ``RESENT_DATA``
        - ``MEAN``
        - Mean number of data packets that had to be resent
    *   - ``HEARTBEAT_COUNT``
        - ``SUM``
        - Total number of ``Heartbeat`` messages
    *   - ``ACKNACK_COUNT``
        - ``SUM``
        - Total number of ``Acknack`` messages
    *   - ``NACKFRAG_COUNT``
        - ``SUM``
        - Total number of ``Nackfrag`` messages
    *   - ``GAP_COUNT``
        - ``SUM``
        - Total number of ``Gap`` messages
    *   - ``DATA_COUNT``
        - ``SUM``
        - Total number of ``Data`` messages
    *   - ``PDP_PACKETS``
        - ``SUM``
        - Total number of PDP packets sent
    *   - ``EDP_PACKETS``
        - ``SUM``
        - Total number of EDP packets sent
