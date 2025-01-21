.. include:: ../exports/alias.include

.. _entities:

########
Entities
########

The monitoring functions of this application relay on tracking the activity of certain *Entities* retrieved by the
*Fast DDS Monitor*, as well as on storing connections and interchanged data between them
for their presentation to the user.
These entities represent DDS communication entities, or different physical elements related to DDS entities.

In the following diagram one can see the different kinds of entities being tracked by the monitor.
The arrows in this schema represent a direct connection (not a 1:n in every case) between both kinds of entities.
Those entities (or types of entities) that do not have a direct relationship are also related, as
intermediate entities make it possible to relate any entity in the graph to one another indirectly,
i.e. one *DomainParticipant* is related with its *User* by the relation with its *Process*.

.. _fig_entities_diagram:

.. figure:: /rst/figures/entities_diagram.svg

.. _dds_entities:

DDS Entities
============

These entities represent the DDS entities that manage the communication. That is, the *DomainParticipants*,
*DataWriters* and *DataReaders*.
Each *DataReader/DataWriter* has one or more associated *Locator* entities.
*Locators* are the network addresses through which *DataReaders/DataWriters* communicate in a DDS network.

For further information about each entity, please refer to the |DDSSpecification| or visit the |FastDDSDocs|.

.. _participant_entity:

DomainParticipant
-----------------
*DomainParticipant* is the main entity in the DDS protocol.
It represents a collection of *DataReaders/DataWriters*, and manages the whole DDS Discovery of other
*DomainParticipants* and *DataReaders/DataWriters* within the DDS Domain to which it belongs.
Refer to `DomainParticipant Fast DDS Documentation
<https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/domain/domainParticipant/domainParticipant.html>`_
for a more detailed explanation of the *DomainParticipant* entity in DDS.

Each *DomainParticipant* can communicate only under a single *Domain*,
(see :ref:`logical entities <logical_entities>` section), which creates a direct connection between each
*DomainParticipant* and the *Domain* in which it operates. Additionally, from the
:ref:`entities diagram <fig_entities_diagram>` it can be seen that *DomainParticipant* entities are contained within
a *Process*. This is because a system process (referred to as a *Process* entity) executes an application using
*Fast DDS*, instantiating *DomainParticipants*. The same applies to *DataReaders* and *DataWriters* instantiated by a
*DomainParticipant* belonging to a specific *Process*. Therefore, a *Process* can contain as many DDS entities as the
*Fast DDS* application running in that *Process* has instantiated.

.. _datawriter_entity:

DataWriter
----------
*DataWriter* is the DDS entity responsible for publishing data.
Each *DataWriter* is directly contained within a single *DomainParticipant*.
In addition, since a *DataWriter* is associated with the *Topic* it publishes under, a direct containment relationship
can be defined between the *DataWriter* and the *Topic*.
Consequently, any *Topic* will contain all the *DataWriters* publishing under it.

Thus, each *DataWriter* is directly connected to the *DomainParticipant* it belongs to
and the *Topic* under which it publishes.
Finally, a *DataWriter* is associated with one or more *Locators*, representing the physical communication
channels it uses to send data.

.. _datareader_entity:

DataReader
----------
*DataReader* is the DDS entity holding the subscribe function in the communication.
As is the case with the *DataWriter*, each *DataReader* is directly contained within a single *DomainParticipant*.
Furthermore, since a *DataReader* is associated to the *Topic* to which it is subscribed,
a direct containment relationship an be established between the *DataReader* and the *Topic*.
As a result, any *Topic* will contain all *DataReaders* subscribed to it.
Therefore, each *DataReader* is directly connected to the *DomainParticipant* it belongs to,
and with the *Topic* to which it is subscribed.

.. _locator_entity:

Locator
-------
*Locator* represents the physical address and port that a *DataReader/DataWriter* uses to send and/or receive data.
This entity is related with the physical division of the entities, as any *Locator* belongs to a unique *Host*
(see section :ref:`physical_entities`).
However, the monitor treats this entity as a *DDS Entity* in order to simplify the entities' connection and improve
comprehensibility.

A *Locator* is connected with one or more *DataReaders/DataWriters*, and so it is related with a *Host*
by connecting each of these *DataReader/DataWriter* with a *DomainParticipant* and each *DomainParticipant* with
its *Host*.

.. _logical_entities:

Logical Entities
================

.. _domain_entity:

Domain
------
*Domain* represents a logical abstraction in the DDS protocol that divides the DDS network into partitions,
making each *Domain* completely independent and unaware of any others.
This logical partition depends on the chosen discovery protocol.

In case of using *Simple Discovery Protocol* (discovery protocol by default in *Fast DDS*) as discovery
mechanism, the *Domain* will be represented by a number (domain ID), and every DDS entity in that *Domain* will discover
the rest of entities deployed on it.
In case of using *Discovery Server* as discovery protocol, the partition will be made by the *Discovery Server*
or *Discovery Servers Net* the monitor connects to. Please refer to
`Fast DDS documentation <https://fast-dds.docs.eprosima.com/en/latest/fastdds/discovery/discovery_server.html>`_ for
more information about this feature.
Each entity connected to a *Discovery Server* on the same network will know all other entities it needs to
communicate with.

This entity inside the monitor is related with the *DomainParticipants* that communicate under this same *Domain*,
and the *Topics* created in this *Domain*.

.. _topic_entity:

Topic
-----
*Topic* is an abstract DDS entity that represents the channel of communications between publishers and subscribers.
Every *DataReader* subscribed to a *Topic* will receive the publications of every *DataWriter*
publishing under the same *Topic*.

This entity inside the monitor is directly connected to the *Domain* it belongs to,
and the *DataReaders/DataWriters* communicating under said *Topic*.

.. _physical_entities:

Physical Entities
=================

.. _host_entity:

Host
----
*Host* makes reference to the physical (or logical i.e. Docker) machine where one or more DDS *Processes*
are running.
This entity is connected directly with the *Users* running in this *Host*.

.. _user_entity:

User
----
*User* makes reference to the different users that run in a *Host*.

This entity is connected directly with the *Host* it belongs to, and the *Processes* that are being executed
within this *User*.

.. _process_entity:

Process
-------
*Process* represents each process running an application using *Fast DDS*. Be aware that it is possible to
run more than one *DomainParticipant* in the same *Process*, and they do not require to be related with
each other, not even under the same *Domain*.

This entity is directly connected to the *User* it belongs to, and the *Participants* running within it.
