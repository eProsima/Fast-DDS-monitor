.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_left_panel:
.. _pro_left_sidebar_layout:

####################
Explorer Panel |Pro|
####################

The left sidebar displays all entities known to the application along with their available information.
It is recommended to read the :ref:`entities` section for an overview of the entity types and
their relationships before using this panel.

The panel contains a variable number of sub-panels: the :ref:`pro_dds_panel_layout`,
:ref:`pro_physical_panel_layout`, :ref:`pro_logical_panel_layout`, and :ref:`pro_info_panel_layout`.
Each sub-panel groups entities by category.
Use the ``...`` button in the upper bar of the panel to show or hide individual sub-panels.
The |refresh| button in the same bar resets the currently selected entity and rebuilds the entity
models from the current database state; use it if entities appear to be missing or the display
seems out of sync (see also :ref:`pro_refresh_button`).
Drag the panel border to resize it.
To hide the entire left sidebar, use **View → Hide Left Sidebar**.

For more information on entity types and their relationships, see :ref:`entities`.
For more information on entity selection, see :ref:`pro_selected_entity`.

.. figure:: /rst/figures/screenshots/explorer_panel_pro.png
    :align: center
    :width: 400px

.. _pro_dds_panel:
.. _pro_dds_panel_layout:

DDS Panel
=========

This panel displays all :ref:`dds_entities` discovered by the monitor across every DDS domain or
Discovery Server being monitored.
The list is filtered to show only the DDS entities related to the currently selected entity
(see :ref:`pro_selected_entity`).
For example, selecting a specific *Host*, *User*, or *Process* shows only the DDS entities running
on that physical context.

Every entity in this panel is interactive:

- Double-click the Participant name or icon to expand or collapse its DataWriters and DataReaders.
- Double-click a DataReader or DataWriter name or icon to expand or collapse its Locators.
- Double-click an entity to set it as the *selected entity*.
  See :ref:`pro_selected_entity` for details.

.. figure:: /rst/figures/screenshots/dds_panel_pro.png
    :align: center

.. _pro_physical_panel:
.. _pro_physical_panel_layout:

Physical Panel
==============

This panel displays all :ref:`physical_entities` discovered by the monitor: *Host*, *User*, and *Process*.
Every entity is interactive:

- Double-click a Host name or icon to expand or collapse its Users.
- Double-click a User name or icon to expand or collapse its Processes.
- Double-click an entity to set it as the *selected entity*.
  See :ref:`pro_selected_entity` for details.

.. figure:: /rst/figures/screenshots/physical_panel_pro.png
    :align: center
    :width: 400px

.. _pro_logical_panel:
.. _pro_logical_panel_layout:

Logical Panel
=============

This panel displays all :ref:`logical_entities` being monitored: *Domain* and *Topic*.
Domains are explicitly configured by the user (see :ref:`monitor_domain`); they cannot be discovered
automatically.
For example, after enabling monitoring of Domain X, any new *DomainParticipant* created in that domain
along with its DataWriters and their topics - will appear in this panel under Domain X.

Every entity is interactive:

- Double-click a Domain name or icon to expand or collapse its Topics.
- Double-click an entity to set it as the *selected entity*.
  See :ref:`pro_selected_entity` for details.

.. figure:: /rst/figures/screenshots/logical_panel_pro.png
    :align: center

.. _pro_info_panel:
.. _pro_info_panel_layout:

Entity Info Panel
=================

This panel displays information about the currently selected entity (see :ref:`pro_selected_entity`).
It has two tabs:

.. _pro_info_subpanel_layout:

Info Panel
----------

Shows the general information of the selected entity.
The fields shown depend on the entity type: for example, a *DDS Entity* shows *QoS* information,
while a *Process* shows its *process ID*.

Some fields are common to all entity types; others are specific to each type:

* **Common fields**

  * **alias**: user-assigned alias
  * **alive**: whether the entity is currently alive
  * **discovery_source**: how the entity was discovered (``discovery`` for DDS discovery protocol,
    ``proxy`` for discovery through statistics messages)
  * **id**: internal unique identifier
  * **kind**: entity type (e.g. host)
  * **metatraffic**: whether the entity processes metatraffic data
  * **name**: internal name of the entity
  * **status**: current status of the entity

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

.. figure:: /rst/figures/screenshots/Info_panel_pro.png
    :align: center

.. _pro_statistics_panel:
.. _pro_statistics_panel_layout:

Statistics Panel
----------------

This panel shows a summary of statistical data for the currently selected entity
(see :ref:`pro_selected_entity`).
Data is aggregated across all entities related to the selected one, using a single bin spanning
all available data.
When no entity is selected, the summary covers all entities in the application.
The values update automatically every 25 seconds; clicking |refresh| forces an immediate update.

.. figure:: /rst/figures/screenshots/statistics_panel_pro.png
    :align: center

The table below lists every data kind shown in this panel together with the aggregation function
applied and a brief description of the metric.
Each value is computed over a single time bin that spans all the data collected since monitoring
started for the relevant entities.

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

.. _pro_selected_entity:

Selected Entity
===============

The application tracks one entity as the **last entity clicked** to determine what information is
displayed throughout the interface.
An entity is any element that can be tracked by the monitor (see :ref:`entities`).

To set an entity as selected, double-click it in any of the Explorer Panel sub-panels.
The selected entity is then used as the context for the whole application.

Selecting an entity has the following effects:

- The entity is highlighted with a blue background until a different entity is selected or the
  selection is cleared.
- The :ref:`pro_info_subpanel_layout` displays the information for that entity, such as its *QoS*
  settings or specific entity properties.
- The :ref:`pro_statistics_panel_layout` shows a statistical summary of the data stored for that
  entity.
- If the selected entity is a Physical or Logical entity, the :ref:`pro_dds_panel_layout` shows only
  the DDS entities related to it.
  Clicking a :ref:`dds_entities` entry in that state does not update the DDS panel.
  See :ref:`entities` for details on entity relationships.

To change the selected entity, double-click a different entity in the Explorer Panel.
To clear the selection entirely, use the **Refresh** button (:ref:`pro_refresh_button`).

When no entity is selected:

- The :ref:`pro_dds_panel_layout` lists all DDS entities across every monitored domain,
  showing all DomainParticipants, DataWriters, and DataReaders regardless of their physical or logical
  context.
- The :ref:`pro_info_panel_layout` shows a brief summary of the overall application state.
