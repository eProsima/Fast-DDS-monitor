.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _left_panel:

##############
Explorer Panel
##############

The left sidebar shows the various entities that the application has knowledge about and their available information.
It is recommended to check the section :ref:`entities` in order to get a better approach on the kind of entities
that are displayed and the connection between them.

.. _dds_panel:

DDS Panel
=========
In this panel are displayed all the :ref:`dds_entities` that has been discovered by the monitor so far under every
DDS domain or Discovery Server monitored.
This panel displays specific DDS entities related with the Fast DDS Monitor entity currently selected
(see :ref:`selected_entity`).
For example, it is possible to track the DDS entities created from an application running on a specific *Host*,
*User*, or *Process*, as well as the DDS entities that are working on a specific DDS domain or are publishing or
subscribed to a given topic.
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
Therefore, this panel will only update the information.
For example, having enabled the monitoring of Domain X,
if an application using Fast DDS creates a new DomainParticipant in that domain with a DataWriter publishing in
Topic Y, the information of that topic will appear in this view listed under Domain X to which
the DomainParticipant discovered by the monitor belongs.

Similar to the :ref:`dds_panel`, every entity in this panel is interactive:

- Clicking in the Domain name or the Domain icon will expand or collapse the list of Topics of the Domain.
- Double clicking in an entity will set this entity as *selected*.
  Please refer to :ref:`selected_entity` for more information on what it means for an entity to be selected.


.. _info_panel:

Info Panel
==========
In this panel it is displayed the specific information of the entity that is currently **selected**
(see :ref:`selected_entity`).
This information has some fields that are general for all the entity kinds, and some others that depends on
the specific entity kind:

* **General fields**

    * **name**: internal name of the entity
    * **id**: internal unique id for each entity

* **Process**

    * **pid**: Process Id in its host

* **Topic**

    * **type_name**: name of the data type of the topic

* **Participant**

    * **GUID**: DDS GUID
    * **QoS**: DDS QoS information

* **DataWriter**

    * **GUID**: DDS GUID
    * **QoS**: DDS QoS information

* **DataReader**

    * **GUID**: DDS GUID
    * **QoS**: DDS QoS information


.. _statistics_panel:

Statistics Panel
================
In this panel it is displayed a summary of some data types of the entity that is currently **selected**
(see :ref:`selected_entity`).
Regarding the selected entity, the data will be fulfilled collecting all the data of all the entities related to the
this one.
The data is calculated by accumulating the data of this entity (using a specific `StatisticKind` in
each case) in one bin from the first to the last data available.
In case there is no selected entity, the information displayed is the group of all the entities that exist in the
application.
The data displayed is the following:

.. list-table::
    :header-rows: 1

    *   - Data Kind
        - Statistic kind
        - Description
    *   - `NETWORK_LATENCY`
        - `MEDIAN`
        - Median value of Network Latency |br|
    *   - `NETWORK_LATENCY`
        - `STANDARD_DEVIATION`
        - Standard deviation of Network Latency |br|
    *   - `FASTDDS_LATENCY`
        - `MEDIAN`
        - Median value of Application Latency |br|
    *   - `FASTDDS_LATENCY`
        - `STANDARD_DEVIATION`
        - Standard deviation value of Application Latency |br|
    *   - `PUBLICATION_THROUGHPUT`
        - `MEDIAN`
        - Median value of Publication Throughput |br|
    *   - `PUBLICATION_THROUGHPUT`
        - `STANDARD_DEVIATION`
        - Standard deviation value of Publication Throughput |br|
    *   - `SUBSCRIPTION_THROUGHPUT`
        - `MEDIAN`
        - Median value of Subscription Throughput |br|
    *   - `SUBSCRIPTION_THROUGHPUT`
        - `STANDARD_DEVIATION`
        - Standard deviation  value of Subscription Throughput |br|
    *   - `RTPS_BYTES_SENT`
        - `MEDIAN`
        - Median value of Total Bytes sent in RTPS packages |br|
    *   - `RTPS_BYTES_LOST`
        - `MEDIAN`
        - Median value of Total Bytes lost in RTPS packages |br|
    *   - `RESENT_DATA`
        - `MEAN`
        - Mean value of Data packages that had to be resent |br|
    *   - `HEARTBEAT_COUNT`
        - `SUM`
        - Total number of `Heartbeat` messages |br|
    *   - `ACKNACK_COUNT`
        - `SUM`
        - Total number of `Acknack` messages |br|
    *   - `NACKFRAG_COUNT`
        - `SUM`
        - Total number of `Nackfrag` messages |br|
    *   - `GAP_COUNT`
        - `SUM`
        - Total number of `Gap` messages |br|
    *   - `DATA_COUNT`
        - `SUM`
        - Total number of `Data` messages |br|
    *   - `PDP_PACKETS`
        - `SUM`
        - Total number of PDP packets sent |br|
    *   - `EDP_PACKETS`
        - `SUM`
        - Total number of EDP packets sent |br|

.. todo::

    Fill descriptions
