.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _right_panel:

#############
Right Sidebar
#############

The right sidebar shows settings about the entities monitored by the application and some general information
about the state and the events of the monitor.

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

.. _status_panel:

Status Panel
============

In this panel it is displayed a brief information of the actual state of the *Fast DDS Monitor*,

* Entities
    * *Domains*: A list of the Domains that has been initialized in the Monitor so far.
    * *Entities*: Total number of entities that are being tracked.

.. _log_panel:

Log Panel
=========

In this panel it is displayed the events that the application has received.
These events arrive in the way of *callbacks* that are generated because of new entities has arrived to
the network or has been discovered, or because it has been any change in the DDS network state.
Each callback contains the entities discovered by the Monitor and the time it has happened.
This list could be erased using :ref:`refresh_button`.

.. _issues_panel:

Issues Panel
============

.. note::
    Work in progress.
    It do not report many information yet.
