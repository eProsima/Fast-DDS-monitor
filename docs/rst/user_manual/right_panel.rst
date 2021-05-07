.. include:: ../exports/alias.include

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

* General fields
    * **name**: internal name of the entity
    * **id**: internal unique id for each entity
* Process
    * **pid**: Process Id in its host
* Topic
    * **type_name**: name of the data type of the topic
* Participant
    * **GUID**: DDS GUID
    * **QoS**: DDS QoS information
* DataWriter
    * **GUID**: DDS GUID
    * **QoS**: DDS QoS information
* DataReader
    * **GUID**: DDS GUID
    * **QoS**: DDS QoS information

.. _statistics_panel:

Statistics Panel
================
In this panel it is displayed a summary of some data types of the entity that is currently **selected**
(see :ref:`selected_entity`).

.. todo::
    Design the information it must display

In case there is no selected entity, the information displayed is the group of all the entities that exist in the
application.

.. _issues_panel:

Issues Panel
============
In this panel it is displayed a brief information of the actual state of the *Fast DDS Monitor*,
as different notifications from events in the application.

* Entities
    * *Domains*: A list of the Domains that has been initialized in the Monitor so far.
    * *Entities*: Total number of entities that are being tracked.
* Callbacks
    * Each of the entities discovered by the Monitor and the time it has happened.
    * This list could be erased using :ref:`refresh_button`.
* Issues
    * Notifications about odd behavior of the application or the DDS networks monitoring.
    * This list could be erased using :ref:`refresh_button`.

.. note::
    *Issues* feature is a work in progress, and may not report many information yet.
